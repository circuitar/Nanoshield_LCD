/*
This is the library to control the LCD Nanoshield

Copyright (c) 2013 Circuitar
This software is released under the MIT license. See the attached LICENSE file for details.
*/

#ifndef NANOSHIELD_LCD_h
#define NANOSHIELD_LCD_h

#include "Arduino.h"

class Nanoshield_LCD: public Print {
  public:
    Nanoshield_LCD(byte a0 = 1, byte a1 = 1, byte a2 = 1);
    void begin();
    void clear();
    void home();
    void setCursor(uint8_t col, uint8_t row); 
    virtual size_t write(uint8_t);
    void cursor();
    void noCursor();
    void blink();
    void noBlink();
    void display();
    void noDisplay();
    void backlight();
    void noBacklight();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void autoscroll();
    void noAutoscroll();
    void leftToRight();
    void rightToLeft();
    void createChar(uint8_t, uint8_t[]);

  private:
    int8_t i2cAddress;
    uint8_t cursorMask;
    uint8_t blinkMask;
    uint8_t displayMask;
    uint8_t backlightMask;
    uint8_t autoscrollMask;
    uint8_t directionMask;

    void writeRegister(uint8_t addr, uint8_t data);
    void writeLcd4(uint8_t data, bool rs);
    void writeLcd8(uint8_t data, bool rs);
    void displayOnOffControl();
    void entryModeSet();
};

#endif