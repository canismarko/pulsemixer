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
  void turnOnLED();
  void updateDisplay();
  void setLineOne(String next_text);
  void setLineTwo(String next_text);
 private:
  gpio_bank _addr;
  GPIOChip _gpio;
  bool _led_on;
  unsigned long _led_on_time;
  void _init();
  void _send_data(gpio_bank i);
  void _send_command(gpio_bank i, bool is4bit=true);
  void setLED(bool setOn);
  void _trigger();
  String _line_one_text = "";
  String _line_two_text = "";
  void writeLines();
};

#endif
