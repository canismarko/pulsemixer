/* 
channel.h - Library for interacting with a channel on the pulsemixer
audio controller.
*/

#ifndef channel_h
#define channel_h

#include "Arduino.h"
#include "GPIO.h"
#include "LCD.h"


class Channel
{
public:
  int setupGPIO();
  gpio_bank getAddr();
  void setupI2C(gpio_bank addr);
  gpio_full readInterruptState();
  void toggleMute();
  void writeGPIO(gpio_full data);
  LCD _lcd;
private:
  gpio_bank _addr = 0x03; // Default no-op address "reserved for future purposes" in I2C
  bool _isMuted = 0;
  GPIOChip _gpio;
};

#endif
