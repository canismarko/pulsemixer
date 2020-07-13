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


void GPIOChip::setPins(gpio_bank reg, gpio_full data, gpio_full pinMask)
{
  // Set only those pins identified by *pinMask* to values in *data*
  gpio_full oldPins = this->readPins();
  data = setBits(oldPins, data, pinMask);
  writeMCP(this -> _addr, reg, data);
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


