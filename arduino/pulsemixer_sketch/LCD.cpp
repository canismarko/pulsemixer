#include "LCD.h"
#include "GPIO.h"

#define LCD_DB      0x0FF0 // B00001111 11110000 // 8-bit mode
#define LCD_DB_4BIT 0x0F00 // B00001111 00000000 // 4-bit mode
#define LCD_ENABLE  0x0008 // B00000000 00001000
#define LCD_RS      0x0004 // B00000000 00000100
#define LCD_RW      0x0020 // B00000000 00100000
#define LCD_LED     0x0010 // B00000000 00010000
#define LCD_ALL LCD_DB_4BIT | LCD_ENABLE | LCD_RS | LCD_RW | LCD_LED

#define LED_TIMEOUT 5000 // In milliseconds
#define LCD_WIDTH 8


void LCD::setupI2C(gpio_bank addr)
{
  _addr = addr;
  _gpio.setupI2C(addr);
  // Set GPIO I/O settings
  gpio_full iodir = 0x0000;
  iodir = iodir & ~LCD_DB_4BIT;
  iodir = iodir & ~LCD_ENABLE;
  iodir = iodir & ~LCD_LED;
  iodir = iodir & ~LCD_RW;
  gpio_full iodir_mask = LCD_DB_4BIT | LCD_ENABLE | LCD_RS | LCD_RW | LCD_LED;
  _gpio.setRegister(IODIRA, iodir, iodir_mask);
  // Initalize the LCD display
  this -> _init();
  // Start with the LEDs off
  this -> setLED(LOW);
}


void LCD::setLineOne(String new_text)
{
  _line_one_text = new_text;
  writeLines();
}


void LCD::setLineTwo(String new_text)
{
  _line_two_text = new_text;
  writeLines();
}


void LCD::updateDisplay()
// Check if the display has changed since it was last refreshed
// If nothing has changed, the display will not be written to.
{
  if (_led_on) {
    // Check if the LED timer has expired
    unsigned long current_timer = millis() - _led_on_time;
    if (current_timer > LED_TIMEOUT) {
      // Timeout has expired, so turn off the LED
      _led_on = false;
      setLED(LOW);
    }
  }
}


void LCD::turnOnLED()
{
  _led_on = true;
  _led_on_time = millis();
  setLED(HIGH);
}


void LCD::setLED(bool setOn)
{
  gpio_full newState;
  if (setOn) {
    newState = 0xFFFF;
  }
  else {
    newState = 0x0000;
  }
  this->_gpio.setPins(GPIOA, newState, LCD_LED);
}


void LCD::writeLines()
{
  Serial.println("Writing lines");
  unsigned char line_length;
  String message;
  // Return home
  _send_command(0x02); // B00000010
  // Write line 1
  message = _line_one_text;
  line_length = min(message.length(), LCD_WIDTH);
  for (int i=0; i<line_length; i++) {
    _send_data(message[i]);
  }
  // Fill out remaining buffer of line 1 with blank spaces
//  for (int i=0; i<40-line_length; i++) {
//    _send_data(' ');
//  }
  _send_data(B10101000);
  _send_data(B11000000);
  // Write line 2
  message = _line_two_text;
  line_length = min(message.length(), LCD_WIDTH);
  for (int i=0; i<line_length; i++) {
    _send_data(message[i]);
  }
  turnOnLED();
}


void LCD::_send_command(gpio_bank command, bool is4bit=true)
{
  gpio_full gpioPins = this->_gpio.readPins();
  // Put first (MSB) 4-bits of command on output port
  gpioPins = setBits(gpioPins, command << 4, LCD_DB_4BIT);
  // D/I=LOW : send instruction (D_I =0)
  gpioPins = setBits(gpioPins, 0x0000, LCD_RS);
  // R/W=LOW : Write (R_W =0)
  gpioPins = setBits(gpioPins, 0x0000, LCD_RW);
  // Clock enable: falling edge
  this->_gpio.setPins(GPIOA, gpioPins, LCD_ALL);
  _trigger();
  // Send the second (LSB) 4-bit chunk
  if (is4bit) {
    gpioPins = setBits(gpioPins, command << 8, LCD_DB_4BIT);
    this->_gpio.setPins(GPIOA, gpioPins, LCD_ALL);
    _trigger();
  }
}


void LCD::_send_data(gpio_bank data)
{
  gpio_full gpioPins = 0x0000;
  // Put first (MSB) 4-bits of data on output port
  gpioPins = setBits(gpioPins, data << 4, LCD_DB_4BIT);
  // D/I=HIGH : send data (D_I =1)
  gpioPins = setBits(gpioPins, 0xFFFF, LCD_RS);
  // R/W=LOW : Write (R_W =0)
  this -> _gpio.setPins(GPIOA, gpioPins, LCD_ALL);
  //Clock enable: falling edge
  _trigger();
  // Send the second (LSB) 4-bit chunk
  gpioPins = setBits(gpioPins, data << 8, LCD_DB_4BIT);
  this->_gpio.setPins(GPIOA, gpioPins, LCD_ALL);
  _trigger();
}


void LCD::_init()
{
  this -> _gpio.setPins(GPIOA, 0x0000, LCD_ENABLE);
  //Wait >40 msec after power is applied
  delay(100);
  // command 0x30 = Wake up
  _send_command(0x30, false); // B00110000
  // must wait 5ms, busy flag not available
  delay(30);
  // command 0x30 = Wake up #2
  _send_command(0x30, false); // B00110000
  //must wait 160us, busy flag not available
  delay(10);
  // command 0x30 = Wake up #3
  _send_command(0x30, false); // B00110000
  //must wait 160us, busy flag not available
  delay(10);
  // Function set: 4-bit
  _send_command(0x20, false); // B00100000
  // Function set: 4-bit/2-line
  _send_command(0x28); // B00101000
  // Set cursor
  _send_command(0x10); // B00010000
  // _send_command(B00011100); // B00011100
  // Display ON; Cursor ON
  _send_command(0x0E); // B00001111
  // Entry mode set
  _send_command(0x06); // B00000110
  // Clear the display
  _send_command(0x01); // B00000001
  // Return home
  _send_command(0x02); // B00000010
}  




void LCD::_trigger()
{
  // Send the enable pulse to trigger the LCD
  this -> _gpio.setPins(GPIOA, 0xFFFF, LCD_ENABLE);
  delay(1);
  this -> _gpio.setPins(GPIOA, 0x0000, LCD_ENABLE);
}
