/*
This is a test for the LCD Nanoshield using the Nanoshield_LCD library.

Copyright (c) 2013 Circuitar
This software is released under the MIT license. See the attached LICENSE file for details.
*/

#include <Wire.h>
#include "Nanoshield_LCD.h"

Nanoshield_LCD lcd;

byte c[8] = {
  B11111,
  B11111,
  B11111,
  B11100,
  B11100,
  B11111,
  B01111,
  B00111,
};

byte i[8] = {
  B10000,
  B11000,
  B11100,
  B00000,
  B11100,
  B11100,
  B11100,
  B11100,
};

void setup() {
  lcd.begin();
  
  // Special characters
  lcd.createChar(0, c);
  lcd.createChar(1, i);
}

void loop() {
  // Clear display and move back to initial position
  lcd.clear();
  delay(1000);
  
  // Special characters
  lcd.write(0);
  lcd.write(1);

  // Printing and positioning
  lcd.print("circuitar");
  lcd.setCursor(8, 1);
  lcd.print("LCD Test");
  delay(2000);
  
  // Printing left-to-right and right-to-left
  lcd.setCursor(15, 0);
  lcd.rightToLeft();
  lcd.print("<");
  lcd.leftToRight();
  
  // Show/hide cursor
  lcd.cursor();
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print(">");
  
  // Blink cursor
  lcd.blink();
  delay(2000);
  lcd.noBlink();
  lcd.noCursor();
  
  // Turn display on or off
  lcd.noDisplay();
  delay(1000);
  lcd.display();
  delay(1000);
  
  // Turn backlight on or off
  lcd.noBacklight();
  delay(1000);
  lcd.backlight();
  delay(1000);

  // Scroll display left and right  
  for (int j = 0; j < 16; j++) {
    lcd.scrollDisplayRight();
    delay(200);
  }
  for (int j = 0; j < 16; j++) {
    lcd.scrollDisplayLeft();
    delay(200);
  }

  // Autoscroll
  lcd.setCursor(15, 0);
  lcd.autoscroll();
  for (int j = 0; j < 16; j++) {
    lcd.write('<');
    delay(200);
  }
  lcd.noAutoscroll();
  
  // Move back to initial position and reset scroll
  lcd.home();
  delay(1000);
}

