/* 
GPIO.h - Library for interacting with the GPIO expander chip on the
pulsemixer audio controller.
*/

#ifndef gpio_h
#define gpio_h

#include "Arduino.h"


typedef uint8_t gpio_bank;
typedef uint16_t gpio_full;


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


//void writeMCP(gpio_bank addr, gpio_bank reg, gpio_bank data);
//void writeMCP(gpio_bank addr, gpio_bank reg, gpio_full data);

// gpio_bank readMCP(gpio_bank addr, gpio_bank reg);

gpio_full combineBanks(gpio_bank byteA, gpio_bank byteB);
gpio_bank splitBankA(gpio_full data);
gpio_bank splitBankB(gpio_full data);


gpio_full setBits(gpio_full oldBits, gpio_full data, gpio_full bitMask);


// One-of debugging helpers
void waitForButton();
void printBinary(gpio_bank input);
void printBinary(gpio_full input);


class GPIOChip
{
 public:
  void setPins(gpio_bank reg, gpio_full data, gpio_full pinMask);
  gpio_full readPins();
  gpio_full readFullRegister(gpio_bank register);
  void setRegister(gpio_bank register_, gpio_bank new_state, gpio_bank pin_mask);
  void setRegister(gpio_bank register_, gpio_full new_state, gpio_full pin_mask);
  static gpio_bank readMCP(gpio_bank addr, gpio_bank reg);
  static void writeMCP(gpio_bank addr, gpio_bank reg, gpio_bank data);
  static void writeMCP(gpio_bank addr, gpio_bank reg, gpio_full data);
  void setupI2C(gpio_bank addr);
  void enableInterrupts(gpio_full pins, gpio_full defval);
  void enableInterrupts(gpio_full pins);
  static bool is_busy() {return (busy_count > 0);}
 private:
  static int raise_busy_count() {busy_count++;}
  static int lower_busy_count() {if (busy_count > 0) busy_count--;}
  gpio_bank _addr;
  static int busy_count;
};


#endif
