/* 
LCD.h - Library for interacting with a channel's LCD of the pulsemixer
audio controller.
*/

#ifndef lcd_h
#define lcd_h

#include "Arduino.h"
#include "GPIO.h"

class LCD
{
 public:
  void setupI2C(gpio_bank newAddr);
  void write(String message);
 private:
  gpio_bank _addr;
  GPIOChip _gpio;
  void _init();
  void _send_data(gpio_bank i);
  void _send_command(gpio_bank i);
  void _trigger();
};

#endif
