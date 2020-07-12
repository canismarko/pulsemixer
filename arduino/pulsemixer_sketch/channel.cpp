#include "Arduino.h"
#include "channel.h"
#include "GPIO.h"


gpio_bank Channel::getAddr() {
  return _addr;
}


void Channel::setupI2C(gpio_bank new_addr) {
  // Save the I2C address for later operations
  _addr = new_addr;
  
  // Set pins to read/write
  writeMCP(_addr, IODIRA, (gpio_bank) B00000000);
  writeMCP(_addr, IODIRB, (gpio_bank) B00000000);

  // Set up hardware interrupts
  writeMCP(_addr, GPINTENA, (gpio_bank) B00000000);
  writeMCP(_addr, GPINTENB, (gpio_bank) B00000000);
  writeMCP(_addr, INTCONA, (gpio_bank) 0x00);
  writeMCP(_addr, INTCONB, (gpio_bank) B00000000);

  // Make buttons report 1 when pressed
  // writeMCP(_addr, IPOLB, (gpio_bank) B00000011);

  // Prepare the LCD to display channel name, etc.
  _lcd.setupI2C(_addr);
}


void Channel::writeGPIO(gpio_full data) {
  writeMCP(_addr, GPIOA, data);
}


gpio_full Channel::readInterruptState() {
  // Read the state of all the GPIO expander pins when the last
  // interrupt was triggered. This also clears the
  // interrupt pin.
}



void Channel::toggleMute() {
  _isMuted != _isMuted;
}
