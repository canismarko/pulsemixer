#include "LCD.h"
#include "GPIO.h"


#define LCD_ALL    0xFFFF // B11111111 11111111
// #define LCD_DB     0xFF00 // B11110000 00000000
// #define LCD_ENABLE 0x0020 // B00000000 00001000
// #define LCD_RS     0x0010 // B00000000 00000100
// #define LCD_RW     0x0008 // B00000000 00000010
#define LCD_DB     0x0FF0 // B00001111 11110000
#define LCD_ENABLE 0x0008 // B00000000 00001000
#define LCD_RS     0x0004 // B00000000 00000100
#define LCD_RW     0x0002 // B00000000 00000010



void LCD::setupI2C(gpio_bank addr)
{
  _addr = addr;
  _gpio.setupI2C(addr);
  this -> _init();
  Serial.println("Finished setup");
  Serial.println("==============");
}


void LCD::write(String message)
{
  for (int i=0; i<message.length(); i++) {
    _send_data(message[i]);
  }
}


void LCD::_send_command(gpio_bank command)
{
  gpio_full gpioPins = this->_gpio.readPins();
  //put data on output Port (P1 = i)
  gpioPins = setBits(gpioPins, command << 4, LCD_DB);
  // D/I=LOW : send instruction (D_I =0)
  gpioPins = setBits(gpioPins, 0x0000, LCD_RS);
  // R/W=LOW : Write (R_W =0)
  gpioPins = setBits(gpioPins, 0x0000, LCD_RW);
  // Clock enable: falling edge
  this->_gpio.setPins(GPIOA, gpioPins, LCD_ALL);
  _trigger();
}


void LCD::_send_data(gpio_bank data)
{
  gpio_full gpioPins = 0x0000;
  // Put data on output Port (P1 = i)
  gpioPins = setBits(gpioPins, data << 4, LCD_DB);
  // D/I=HIGH : send data (D_I =1)
  gpioPins = setBits(gpioPins, 0xFFFF, LCD_RS);
  // R/W=LOW : Write (R_W =0)
  this -> _gpio.setPins(GPIOA, gpioPins, LCD_ALL);
  //Clock enable: falling edge
  _trigger();
}


void LCD::_init()
{
  this -> _gpio.setPins(GPIOA, 0x0000, LCD_ENABLE);
  //Wait >40 msec after power is applied
  delay(100);
  // command 0x30 = Wake up
  _send_command(0x30); // B00110000
  // must wait 5ms, busy flag not available
  delay(30);
  // command 0x30 = Wake up #2
  _send_command(0x30); // B00110000
  //must wait 160us, busy flag not available
  delay(10);
  // command 0x30 = Wake up #3
  _send_command(0x30); // B00110000
  //must wait 160us, busy flag not available
  delay(10);
  //Function set: 8-bit/2-line
  _send_command(0x38); // B00111000
  // Set cursor
  _send_command(0x10); // B00010000
  // _send_command(B00011100); // B00011100
  // Display ON; Cursor ON
  _send_command(0x0c); // B00001111
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
