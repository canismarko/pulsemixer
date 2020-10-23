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
  gpio_full readInterruptFlags();
  void toggleMute();
  void writeGPIO(gpio_full data);
  void setInterruptFlag();
  bool volumeIsDirty();
  void clearVolumeDirty();
  bool processInterrupts();
  void bumpVolume(int vol_change);
  void updateOutputs();
  void setShortName(String new_name);
  void setID(int new_id) {_id = new_id;}
  int getID() {return _id;}
  void showChannelName();
// private:
  unsigned long _last_volume_change = 0;
  unsigned long _last_volume_touched = 0;
  bool _volume_dirty = false;
  int _volume = 0;
  String _short_name;
  int _id = -1;
  bool _interrupt_flag = false;
  byte _vol_old_pins = B00;
  gpio_bank _addr = 0x03; // Default no-op address "reserved for future purposes" in I2C spec
  bool _isMuted = 0;
  GPIOChip _gpio;
  LCD _lcd;
};

#endif
