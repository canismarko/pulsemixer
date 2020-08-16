#include "Arduino.h"
#include "channel.h"
#include "GPIO.h"
#include <Wire.h>


void GPIOChip::setupI2C(gpio_bank addr)
{
  _addr = addr;
}


gpio_full setBits(gpio_full oldBits, gpio_full data, gpio_full bitMask)
{
  // Set only those bits identified by *bitMask* to values in *data*
  oldBits &= (~bitMask);
  data &= bitMask;
  data |= oldBits;
  return data;
}


void printBinary(gpio_bank input) {
  for (char i=sizeof(input)*8-1; i>=0; i--) {
    Serial.print(bitRead(input, i));
  }
}

void printBinary(gpio_full input) {
  for (char i=sizeof(gpio_bank)*16-1; i>=sizeof(gpio_bank)*8; i--) {
    Serial.print(bitRead(input, i));
  }
  Serial.print("|");
  for (char i=sizeof(gpio_bank)*8-1; i>=0; i--) {
    Serial.print(bitRead(input, i));
  }
}


void waitForButton() {
  return;
  Serial.print("Waiting for button...");
  int state = 1;
  while (state) {
    state = digitalRead(4);
    delay(100);
  }
  // Now wait for the button to come back up
  while (!state) {
    state = digitalRead(4);
    delay(100);
  }
  Serial.println("done");
}


gpio_full GPIOChip::readPins() {
  return combineBanks(readMCP(this->_addr, GPIOA), readMCP(this->_addr, GPIOB));
}

gpio_full GPIOChip::readFullRegister(gpio_bank register_){
  return combineBanks(readMCP(_addr, register_), readMCP(_addr, register_ + 1));
}

void GPIOChip::setRegister(gpio_bank register_, gpio_bank new_state, gpio_bank pin_mask)
{
  gpio_bank old_state = readMCP(_addr, register_);
  new_state = setBits(old_state, new_state, pin_mask);
  writeMCP(_addr, register_, new_state);
}


void GPIOChip::setRegister(gpio_bank register_, gpio_full new_state, gpio_full pin_mask)
{
  setRegister(register_, splitBankA(new_state), splitBankA(pin_mask));
  setRegister(register_+1, splitBankB(new_state), splitBankB(pin_mask));
}


void GPIOChip::setPins(gpio_bank reg, gpio_full data, gpio_full pinMask)
{
  // Set only those pins identified by *pinMask* to values in *data*
  gpio_full oldPins = this->readPins();
  data = setBits(oldPins, data, pinMask);
  writeMCP(this -> _addr, reg, data);
}


void GPIOChip::enableInterrupts(gpio_full pins)
// Enable interrupt response on certain pins on any change.
// 
// Parameters
// ==========
// pins
//   16-bits (GPIOA GPIOB) where 1's enable interrupt on that pin
{
  // Read current state of interrupt pins
  gpio_full int_state = combineBanks(readMCP(this->_addr, GPINTENA), readMCP(this->_addr, GPINTENB));
  // Toggle the requested pins
  int_state = int_state | pins;
  // Write new pins state to the gpio chip
  writeMCP(_addr, GPINTENA, int_state);
  
  // Set interrupt contro register to trigger on change
  gpio_full con_state = combineBanks(readMCP(this->_addr, INTCONA), readMCP(this->_addr, INTCONB));
  // Toggle the requested pins
  con_state = con_state & ~pins;
  // Write back to the gpio chip
  writeMCP(_addr, INTCONA, con_state);
}


void GPIOChip::enableInterrupts(gpio_full pins, gpio_full defval)
// Enable interrupt response on certain pins compared to specific values.
// 
// Parameters
// ==========
// pins
//   16-bits (GPIOA GPIOB) where 1's enable interrupt on that pin
// defval
//   16-bits (GPIOA GPIOB) with values that will trigger an interrupt on the pin
{
  // Enable requested interrupt pins
  // Read current default states
  gpio_full int_state = combineBanks(readMCP(this->_addr, GPINTENA), readMCP(this->_addr, GPINTENB));
  // Toggle the requested pins
  int_state = int_state | pins;
  // Write new pins state to the gpio chip
  writeMCP(_addr, GPINTENA, int_state);
  
  // Set interrupt control register to trigger on change
  // Read current default states
  gpio_full con_state = combineBanks(readMCP(this->_addr, INTCONA), readMCP(this->_addr, INTCONB));
  // Toggle the requested pins
  con_state = con_state | pins;
  // Write back to the gpio chip
  writeMCP(_addr, INTCONA, con_state);

  // Set default values
  // Read current default states
  gpio_full defval_state = combineBanks(readMCP(this->_addr, DEFVALA), readMCP(this->_addr, DEFVALB));
  // Toggle the requested pins
  gpio_full masked_defval = defval & pins;
  defval_state = (defval_state & ~pins) | masked_defval;
  // Write back to the GPIO chip
  writeMCP(_addr, DEFVALA, defval_state);
}

gpio_full combineBanks(gpio_bank dataA, gpio_bank dataB) {
  gpio_full newStates = (dataA<<8) | dataB;
  return newStates;
}


gpio_bank splitBankA(gpio_full data) {
  gpio_bank newState = (data>>8);
  return newState;
}


gpio_bank splitBankB(gpio_full data) {
  gpio_bank newState = (data & 0x00FF);
  return newState;
}


gpio_bank readMCP(gpio_bank addr, gpio_bank reg) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(addr, (gpio_bank) 1);
  gpio_bank response = Wire.read();
  return response;
}


void writeMCP(gpio_bank addr, gpio_bank reg, gpio_bank data) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}


void writeMCP(gpio_bank addr, gpio_bank reg, gpio_full data) {
  gpio_bank dataA, dataB;
  dataA = splitBankA(data);
  dataB = splitBankB(data);
  
  writeMCP(addr, reg, dataA);
  writeMCP(addr, reg+1, dataB);
}
