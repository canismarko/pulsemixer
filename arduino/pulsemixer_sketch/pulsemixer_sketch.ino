#include <Wire.h>
#include "channel.h"

// Arduino pins
#define PIN_INT_BTN 2
#define PIN_INT_ROT 3

// i2c address for GPIO port expanders
#define GPIO_CH0 0x20
#define GPIO_CH1 0x21
#define GPIO_CH2 0x22
#define GPIO_CH3 0x23

#define TICK 300

// MCP23017 control registers
#define IODIRA   0x00
#define IODIRB   0x01
#define IPOLA    0x02
#define IPOLB    0x03
#define GPINTENA 0x04
#define GPINTENB 0x05
#define DEFVALA  0x06
#define DEFVALB  0x07
#define INTCONA  0x08
#define INTCONB  0x09
#define INTCAPA  0x10
#define INTCAPB  0x11
#define INTFA    0x0E
#define INTFB    0x0F 
#define GPIOA    0x12
#define GPIOB    0x13

// Masks for GPIO pin assignments
#define BTN_MUTE B00000001
#define BTN_VOL  B00000010
#define ROT_VOLB B00100000
#define ROT_VOLA B01000000
#define ROT_VOLS (ROT_VOLA | ROT_VOLB)

// Variables for tracking rotary encoder
byte volOldPins[] = {0, 0, 0, 0}; // will hold state of pins last time encoder was read
const byte RotaryDecodeTable[4][4] = {  // Declare array RotaryDecodeTable
{B00, B10, B01, B11},
{B01, B00, B11, B10},
{B10, B11, B00, B01},
{B11, B01, B10, B00}
};
int rotationCounters[] = {0, 0, 0, 0};

// State variables
bool muteButtonsPressed[] = {0, 0, 0, 0};
byte inputALast = 0;


byte readGPIO(byte addr, byte reg, bool is_interrupt=false);


void writeMCP(byte addr, byte reg, byte data) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

byte readGPIO(byte addr, byte reg, bool is_interrupt=false) {
  if (is_interrupt) {
    // Fix the interrupt problem with i2c
    // https://www.best-microcontroller-projects.com/mcp23017.html
    noInterrupts();
  
    // Debounce. Slow I2C: extra debounce between interrupts anyway.
    // Can not use delay() in interrupt code.
    delayMicroseconds(1000);
   
    // Stop interrupts from external pin.
    // detachInterrupt(digitalPinToInterrupt(PIN_INT_BTN));
    detachInterrupts();
      interrupts(); // re-start interrupts for mcp
  }

  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(addr, (byte) 1);
  byte response = Wire.read();

  if (is_interrupt) {
  
    attachInterrupts();  // Reinstate interrupts from external pin.
  }
  
  return response;
}

void setupI2C() {
    // Set up the i2c interface
  Wire.begin();

  // Set pins to read/write
  writeMCP(GPIO_CH0, IODIRA, B11110000);
  writeMCP(GPIO_CH0, IODIRB, B00000011);

  // Set up hardware interrupts
  writeMCP(GPIO_CH0, GPINTENA, B11100000);
  writeMCP(GPIO_CH0, GPINTENB, B00000011);
  writeMCP(GPIO_CH0, INTCONA, 0x00);
  writeMCP(GPIO_CH0, INTCONB, B00000000);
  // writeMCP(GPIO_CH0, DEFVALB, B00000011);

  // Make buttons report 1 when pressed
  writeMCP(GPIO_CH0, IPOLB, B00000011);

}

void turnOnLED() {
  Wire.beginTransmission(GPIO_CH0);
  Wire.write(GPIOA);
  Wire.write(0xFF);
  Wire.endTransmission();
}

void turnOffLED() {
  Wire.beginTransmission(GPIO_CH0);
  Wire.write(GPIOA);
  Wire.write(0x00);
  Wire.endTransmission();
}


void readVolumeEncoder() {
  Wire.beginTransmission(GPIO_CH0);
  Wire.write(GPIOA);
  Wire.endTransmission();
  Wire.requestFrom(GPIO_CH0, 1);
  byte inputs = Wire.read();
  // Extract just the volume A/B bits
  bool volA = (inputs & B01000000);
  bool volB = inputs & B00100000;
  if (inputs != inputALast) {
    inputALast = inputs;
    Serial.println("Input changed!");
    Serial.print("Inputs: ");
    Serial.println(inputs, BIN);
    Serial.print("Vol A: ");
    Serial.println(volA);
    Serial.print("Vol B: ");
    Serial.println(volB);
  }
  
  
}


void attachInterrupts() {
  attachInterrupt(digitalPinToInterrupt(PIN_INT_ROT), isr_volume, LOW);
  attachInterrupt(digitalPinToInterrupt(PIN_INT_BTN), isr_button, LOW);
}

void detachInterrupts() {
  detachInterrupt(digitalPinToInterrupt(PIN_INT_ROT));
  detachInterrupt(digitalPinToInterrupt(PIN_INT_BTN));
}

void isr_volume() {
  int channel = 0;
  // Load current state of the volume knobs
  byte gpio_states = readGPIO(GPIO_CH0, INTCAPA, true);
  byte new_vols = ((gpio_states & ROT_VOLS) >>5);
  // Determine if the volume knob has moved
  byte vol_move = RotaryDecodeTable[volOldPins[channel]][new_vols]; // used RotaryDecodeTable to decide movement, if any
  volOldPins[channel] = new_vols; // update encoder1state to be current pin values
  if (vol_move == B10){ // if result was move right (CW), increment counter
    rotationCounters[channel]++;
  }
  if (vol_move == B01){ // if result was move left (anti-CW), decrement counter
    rotationCounters[channel]--;
  }
  Serial.println(rotationCounters[channel]);
}

void isr_button() {

  // Load current state of which buttons were pressed
  byte states = readGPIO(GPIO_CH0, INTCAPB, true);
  bool mute_button_down = (bool) (states & BTN_MUTE);
  muteButtonsPressed[0] = muteButtonsPressed[0] || mute_button_down;
  Serial.println(muteButtonsPressed[0]); 
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  setupI2C();

  // Attach hardware interrupts to service routines
  pinMode(PIN_INT_ROT, INPUT);
  pinMode(PIN_INT_BTN, INPUT);
  attachInterrupts();

  // Clear interrupt registers
  readGPIO(GPIO_CH0, INTCAPA);
  readGPIO(GPIO_CH0, INTCAPB);
}


void loop() {
  // put your main code here, to run repeatedly:
  
  // Sleep for a second
  delay(TICK);
}
