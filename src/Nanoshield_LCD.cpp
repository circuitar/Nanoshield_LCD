/**
 * @file This is the library to control the LCD Nanoshield
 * 
 * Copyright (c) 2013 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
 */
#include "Arduino.h"
#include <Wire.h>
#include "Nanoshield_LCD.h"

#define LCD_I2C_ADDRESS 0x27

// Bit masks
#define DISPLAY_ON     0x04
#define DISPLAY_OFF    0x00
#define CURSOR_ON      0x02
#define CURSOR_OFF     0x00
#define BLINK_ON       0x01
#define BLINK_OFF      0x00
#define BACKLIGHT_ON   0x80
#define BACKLIGHT_OFF  0x00
#define AUTOSCROLL_ON  0x01
#define AUTOSCROLL_OFF 0x00
#define LEFT_TO_RIGHT  0x02
#define RIGHT_TO_LEFT  0x00

Nanoshield_LCD::Nanoshield_LCD(byte a0, byte a1, byte a2) {
  // Select the three LSBs of the LCD address in the I2C bus
  i2cAddress = LCD_I2C_ADDRESS;
  if (!a0) i2cAddress &= 0x01;
  if (!a1) i2cAddress &= 0x02;
  if (!a2) i2cAddress &= 0x04;
  displayMask = DISPLAY_ON;
  cursorMask = CURSOR_OFF;
  blinkMask = BLINK_OFF;
  backlightMask = BACKLIGHT_ON;
  autoscrollMask = AUTOSCROLL_OFF;
  directionMask = LEFT_TO_RIGHT;
}

void Nanoshield_LCD::writeRegister(uint8_t addr, uint8_t data)
{
  Wire.beginTransmission(i2cAddress);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
}

void Nanoshield_LCD::writeLcd4(uint8_t data, bool rs)
{
  // Use only lower 4 bits of data
  data &= 0x0F;

  // Set to pin GP7 in MCP23008 to high if backlight is on
  data |= backlightMask;
  if (rs) data |= 0x40;
  writeRegister(0x0A, data);

  // Raise clock line
  data |= 0x10;
  writeRegister(0x0A, data);

  // Lower clock line
  data &= ~0x10;
  writeRegister(0x0A, data);
  delay(1);
}

void Nanoshield_LCD::writeLcd8(uint8_t data, bool rs)
{
  writeLcd4((data >> 4) & 0x0F, rs);
  writeLcd4(data & 0x0F, rs);
}

void Nanoshield_LCD::displayOnOffControl()
{
  writeLcd8(0x08 | displayMask | cursorMask | blinkMask, false);
}

void Nanoshield_LCD::entryModeSet()
{
  writeLcd8(0x04 | directionMask | autoscrollMask, false);
}

void Nanoshield_LCD::begin()
{
  // Initiate the Wire library and join the I2C bus as a master
  Wire.begin();
  
  // Configure all GPIO pins in MCP23008 as outputs and leave everything else as default
  writeRegister(0x00, 0x00);
  
  // Perform LCD reset by instruction in 4-bit mode as described in the HD44780 datasheet
  delay(50);
  writeLcd4(0x03, false);
  delay(5);
  writeLcd4(0x03, false);
  delayMicroseconds(100);
  writeLcd4(0x03, false);
  delay(5);
  writeLcd4(0x02, false);
  writeLcd8(0x28, false);
  writeLcd8(0x08, false); // Two lines, 5x8 dots per character
  writeLcd8(0x01, false);
  writeLcd8(0x06, false); // When writing, increment address and do not shift the display
  writeLcd8(0x0C, false);
  delayMicroseconds(100);
}

void Nanoshield_LCD::clear()
{
  writeLcd8(0x01, false);
}

void Nanoshield_LCD::home()
{
  writeLcd8(0x02, false);
  delay(1);
}

void Nanoshield_LCD::setCursor(uint8_t col, uint8_t row)
{
  // Get address in the first row
  uint8_t addr = col & 0x3F;
  
  // Add row offset
  addr += (row % 2 * 0x40) + (row / 2 * 20);

  // Set DDRAM address
  writeLcd8(addr | 0x80, false);
}

size_t Nanoshield_LCD::write(uint8_t data)
{
  writeLcd8(data, true);
  return 1;
}

void Nanoshield_LCD::cursor()
{
  cursorMask = CURSOR_ON;
  displayOnOffControl();
}

void Nanoshield_LCD::noCursor()
{
  cursorMask = CURSOR_OFF;
  displayOnOffControl();
}

void Nanoshield_LCD::blink()
{
  blinkMask = BLINK_ON;
  displayOnOffControl();
}

void Nanoshield_LCD::noBlink()
{
  blinkMask = BLINK_OFF;
  displayOnOffControl();
}

void Nanoshield_LCD::display()
{
  displayMask = DISPLAY_ON;
  displayOnOffControl();
}

void Nanoshield_LCD::noDisplay()
{
  displayMask = DISPLAY_OFF;
  displayOnOffControl();
}

void Nanoshield_LCD::backlight()
{
  backlightMask = BACKLIGHT_ON;
  writeRegister(0x0A, backlightMask);
}

void Nanoshield_LCD::noBacklight()
{
  backlightMask = BACKLIGHT_OFF;
  writeRegister(0x0A, backlightMask);
}

void Nanoshield_LCD::scrollDisplayLeft()
{
  writeLcd8(0x18, false);
}

void Nanoshield_LCD::scrollDisplayRight()
{
  writeLcd8(0x1C, false);
}

void Nanoshield_LCD::autoscroll()
{
  autoscrollMask = AUTOSCROLL_ON;
  entryModeSet();
}

void Nanoshield_LCD::noAutoscroll()
{
  autoscrollMask = AUTOSCROLL_OFF;
  entryModeSet();
}

void Nanoshield_LCD::leftToRight()
{
  directionMask = LEFT_TO_RIGHT;
  entryModeSet();
}

void Nanoshield_LCD::rightToLeft()
{
  directionMask = RIGHT_TO_LEFT;
  entryModeSet();
}

void Nanoshield_LCD::createChar(uint8_t num, uint8_t data[])
{
  if (num > 7) return;

  // Address character position in CGRAM
  writeLcd8(0x40 | (num << 3), false);
  
  // Write character in CGRAM
  for (int i = 0; i < 8; i++) {
    writeLcd8(data[i], true);
  }
}
