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
  void turnOffLED();
  void updateDisplay();
  void setLineOne(String next_text);
  void setLineTwo(String next_text);
  void writeLines();
  void showVolume(int new_volume);
 private:
  gpio_bank _addr;
  GPIOChip _gpio;
  bool led_on;
  bool _is_ready = false;
  unsigned long led_on_time;
  void _init();
  unsigned char _send_message(String message, String old_message, unsigned char cursor_offset);
  void _send_data(gpio_bank i);
  void _moveCursor(unsigned char pos);
  void _send_command(gpio_bank i, bool is4bit=true);
  void setLED(bool setOn);
  void _trigger();
  String _line_one_text = "        ";
  String _line_one_text_old = "        ";
  String _line_two_text = "        ";
  String _line_two_text_old = "        ";
};

#endif
