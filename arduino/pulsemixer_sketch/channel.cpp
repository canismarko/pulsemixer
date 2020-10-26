#include "Arduino.h"
#include "channel.h"
#include "GPIO.h"

// #define DEBUG

#define MUTE_LED 0x8000 // B10000000 00000000
#define VOL_SW   0x4000 // B01000000 00000000
#define MUTE_SW  0x2000 // B00100000 00000000
#define VOL_A    0x0001 // B00000000 00000001
#define VOL_B    0x0002 // B00000000 00000010
#define VOLS     (VOL_A | VOL_B)

#define MIN_VOL 0
#define MAX_VOL 100

volatile boolean isr_is_running = false;


const byte RotaryDecodeTable[4][4] = {  // Declare array RotaryDecodeTable
{B00, B10, B01, B11},
{B01, B00, B11, B10},
{B10, B11, B00, B01},
{B11, B01, B10, B00}
};


gpio_bank Channel::getAddr() {
  return _addr;
}


void Channel::setupI2C(gpio_bank new_addr) {
  // Save the I2C address for later operations
  _addr = new_addr;
  _gpio.setupI2C(_addr);
  // _short_name = "Addr: " + String(_addr, HEX);
  // Set pins to read/write
  // Input pins
  gpio_full iodir = 0x0000;
  gpio_full io_mask = MUTE_LED | VOL_SW | MUTE_SW | VOL_A | VOL_B;
  iodir = iodir | MUTE_SW;
  iodir = iodir | VOL_SW;
  iodir = iodir | VOL_A;
  iodir = iodir | VOL_B;
  // Output pins
  iodir = iodir & ~MUTE_LED;
  _gpio.setRegister(IODIRA, iodir, io_mask);

  // Set up hardware interrupts
  // writeMCP(_addr, GPINTENA, (gpio_bank) B00000000);
  // writeMCP(_addr, GPINTENB, (gpio_bank) B00000000);
  // writeMCP(_addr, INTCONA, (gpio_bank) 0x00);
  // writeMCP(_addr, INTCONB, (gpio_bank) B00000000);
  _gpio.enableInterrupts(VOL_A | VOL_B);
  _gpio.enableInterrupts(VOL_SW | MUTE_SW);

  // Make buttons report 1 when pressed
  // writeMCP(_addr, IPOLB, (gpio_bank) B00000011);

  // Prepare the LCD to display channel name, etc.
  _lcd.setupI2C(_addr);
  showChannelName();

}

void Channel::showChannelName() {
  _lcd.setLineOne(_short_name);
}
  

void Channel::writeGPIO(gpio_full data) {
  _gpio.writeMCP(_addr, GPIOA, data);
}


void Channel::setInterruptFlag() {
  // Checker to see if we're already in an ISR
  if(isr_is_running || _gpio.is_busy()) return; //we have been interrupted while already processing an interrupt - ignore this ocurrence
  _interrupt_flag = true;
  isr_is_running = true;
  interrupts(); //re-enable interrupts so that interrupt-based functions can be used inside this function
  // Check if this is a volume knob event
  gpio_full int_state = readInterruptState();
  // Determine which inputs triggered the interrupt
  // gpio_full int_triggered = readInterruptFlags();
  // Disable interrupts so we can keep running this function
  
  isr_is_running = false;
  // Extract the volume rotary encoder A/B bits
  byte new_vols = (int_state & VOLS);
  byte vol_move = RotaryDecodeTable[_vol_old_pins][new_vols]; // used RotaryDecodeTable to decide movement, if any
  _vol_old_pins = new_vols;
  // Set the pending volume to the current volume if it's not dirty
  if (!_volume_dirty)
    pending_volume = _volume;
  if (vol_move == B10){ // if result was move right (CW), increment counter
    pending_volume += 3;
    _volume_dirty = true;
  }
  if (vol_move == B01){ // if result was move left (anti-CW), decrement counter
    pending_volume -= 3;
    _volume_dirty = true;
  }
  noInterrupts(); //turn off interrupts so we can't be interrupted while resetting our special variable
  
}


void Channel::setVolume(int new_volume) {
  unsigned long current_time = micros();
  if (current_time - _last_volume_change > 10000) {
    if (new_volume < MIN_VOL) {
      new_volume = MIN_VOL;
    } else if (new_volume > MAX_VOL) {
      new_volume = MAX_VOL;
    }
    #ifdef DEBUG
    Serial.print("Setting new volume ");
    Serial.print(_id);
    Serial.print(": ");
    Serial.println(new_volume);
    #endif
    _volume = new_volume;
    pending_volume = _volume;
    // Update the LCD
    _lcd.showVolume(_volume);
    _lcd.turnOnLED();
    // Send new volume to the host
    Serial.print("!set volume ");
    Serial.print(_id);
    Serial.print(" ");
    Serial.println(_volume);
  }
  _last_volume_change = current_time;
}


void Channel::bumpVolume(int vol_change) {
  setVolume(_volume + vol_change);
}


void Channel::updateOutputs() {
  _lcd.updateDisplay();
}


bool Channel::processInterrupts() {
  if (_volume_dirty) {
    _volume_dirty = false;
    #ifdef DEBUG
    Serial.print("Volume changed: ");
    Serial.println(pending_volume);
    #endif
    // _volume = bumpVolume(pending_volume);
    Channel::setVolume(pending_volume);
  }
  // Returns true if the volume encoder was moved
  if (_interrupt_flag) {
    _interrupt_flag = false;
    gpio_full int_state = readInterruptState();
    // Determine which inputs triggered the interrupt
    gpio_full int_triggered = readInterruptFlags();
    // Extract the volume rotary encoder A/B bits
//    byte new_vols = (int_state & VOLS);
//    if (new_vols != _vol_old_pins)
//      _last_volume_touched = micros();
//    byte vol_move = RotaryDecodeTable[_vol_old_pins][new_vols]; // used RotaryDecodeTable to decide movement, if any
//    _vol_old_pins = new_vols;
//    if (vol_move == B10){ // if result was move right (CW), increment counter
//      bumpVolume(1);
//    }
//    if (vol_move == B01){ // if result was move left (anti-CW), decrement counter
//      bumpVolume(-1);
//    }
  
    if (~int_state & MUTE_SW) {
      // Serial.println("Mute switch pressed");
      toggleMute();
    }
    if (~int_state & VOL_SW) {
      // Serial.println("Volume switch pressed");
      _lcd.turnOnLED();
    }
  }
  return (micros() - _last_volume_touched < 20000);
}


gpio_full Channel::readInterruptState() {
  // Read the state of all the GPIO expander pins when the last
  // interrupt was triggered. This also clears the
  // interrupt pin.
  gpio_full int_state = _gpio.readFullRegister(INTCAPA);
  return int_state;
}

gpio_full Channel::readInterruptFlags() {
  // Read the interrupt flags showing which pins in the GPIO expander 
  // triggered the last interrupt. This does not clear the
  // interrupt pin.
  gpio_full int_state = _gpio.readFullRegister(INTFA);
  return int_state;
}



void Channel::setMute(bool new_mute_state) {
  _isMuted = new_mute_state;
  if (_isMuted) {
    _gpio.setPins(GPIOA, 0xFFFF, MUTE_LED);
    _lcd.setLineTwo("Muted   ");
  } else {
    _gpio.setPins(GPIOA, 0x0000, MUTE_LED);
    _lcd.setLineTwo("Unmuted ");
  }
  _lcd.writeLines();
  _lcd.turnOnLED();
}


void Channel::toggleMute() {
  bool new_mute_state = !_isMuted;
  setMute(new_mute_state);
  // Notify the host
  Serial.print("!mute ");
  Serial.print(_id);
  Serial.print(" ");
  Serial.println(_isMuted);
}


void Channel::setShortName(String new_name) {
  _short_name = new_name;
  showChannelName();
}
