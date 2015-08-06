/**
 * @file This is the library to control the LCD Nanoshield
 * 
 * Copyright (c) 2013 Circuitar
 * This software is released under the MIT license. See the attached LICENSE
 * file for details.
 */
#ifndef NANOSHIELD_LCD_h
#define NANOSHIELD_LCD_h

#include "Arduino.h"


class Nanoshield_LCD: public Print {
  public:
    /**
     * Constructor
     * 
     * Creates an object to access one LCD Nanoshield
     * 
     * @param a0 The 1st LSB of the LCD addressin the I2C bus.
     * @param a1 The 2nd LSB of the LCD addressin the I2C bus.
     * @param a2 The 3rd LSB of the LCD addressin the I2C bus.
     * 
     * @see begin()
     */
    Nanoshield_LCD(byte a0 = 1, byte a1 = 1, byte a2 = 1);

    /**
     * Initializes the module.
     * 
     * Initialize the Wire library, join the I2C bus as a master, configure 
     * GPIO pins, perform LCD reset by instruction in 4-bit mode, set as two
     * lines, 5x8 characters and to, when writing, increment address and do 
     * not shift the display.
     */
    void begin();

    /**
     * Clears all the characters from display.
     */
    void clear();

    /**
     * Sets the cursor to initial position.
     */
    void home();

    /**
     * Sets the cursor position.
     * 
     * @param col The cursor column.
     * @param row The cursor row.
     */
    void setCursor(uint8_t col, uint8_t row);

    /**
     * Writes a special character.
     * 
     * Writes a character pre-specified with createChar().
     * 
     * @param  data The code of the character to write.
     * @return Always returns 1.
     */
    virtual size_t write(uint8_t data);

    /**
     * Set the cursor as visible.
     */
    void cursor();

    /**
     * Hides the cursor.
     */
    void noCursor();

    /**
     * Set the cursor as blinking.
     */
    void blink();

    /**
     * Sets the cursor as not blinking.
     */
    void noBlink();

    /**
     * Turns the display on.
     */
    void display();

    /**
     * Turns the display off.
     */
    void noDisplay();

    /**
     * Turns backlight on.
     */
    void backlight();

    /**
     * Turns backlight off.
     */
    void noBacklight();

    /**
     * Scrolls all the content on display to left.
     */
    void scrollDisplayLeft();

    /**
     * Scrolls all the content on display to right.
     */
    void scrollDisplayRight();

    /**
     * Scrolls the display as needed while writing data.
     */
    void autoscroll();

    /**
     * Do not scroll the display as needed while writing data.
     */
    void noAutoscroll();

    /**
     * Moves the cursor to right when writes a character.
     */
    void leftToRight();

    /**
     * Moves the cursor to left when writes a character.
     */
    void rightToLeft();

    /**
     * Creates a special character.
     * 
     * Creates a special character based on a byte vector of 8 elements. Each
     * element represents a line of the character and must be composed of five
     * bits, one for each column. If the bit is 1, so that pixel will be on,
     * if the bit is zero, so that pixel will be off.
     * 
     * @param num A code to index the character from 0 to 7.
     * @param data The vector representation of the character.
     */
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