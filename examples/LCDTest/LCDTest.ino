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
  lcd.createChar(0, c);
  lcd.createChar(1, i);
}

void loop() {
  delay(1000);
  lcd.setCursor(8, 1);
  lcd.print("LCD Test");
  delay(1000);
  lcd.home();
  lcd.write(0);
  lcd.write(1);
  lcd.print("circuitar");
  delay(1000);
  lcd.setCursor(15, 0);
  lcd.rightToLeft();
  lcd.print("<");
  lcd.leftToRight();
  lcd.cursor();
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print(">");
  lcd.blink();
  delay(2000);
  lcd.noDisplay();
  delay(1000);
  lcd.noBacklight();
  delay(1000);
  lcd.backlight();
  delay(1000);
  lcd.display();
  lcd.noCursor();
  lcd.noBlink();
  delay(1000);
  
  for (int j = 0; j < 16; j++) {
    lcd.scrollDisplayRight();
    delay(200);
  }
  
  for (int j = 0; j < 16; j++) {
    lcd.scrollDisplayLeft();
    delay(200);
  }
  
  delay(1000);
  lcd.clear();
}

