/*******************************************************************************
  ScrollTextLibrary
  NoiascaLiquidCrystal_I2C

  This is a demo Sketch to show how to scroll the LCD Display with the library method
  This demo is non-blocking - without any delay

  name=ScrollTextLibrary
  version=1.0.1
  author=noiasca

  Version 
  2022-04-17
  
 *******************************************************************************/

#include <Wire.h>
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm  
#include <NoiascaHW/lcd_PCF8574.h>     // include the proper IO interface

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x3F;                // most used LCD address is 0x3F or 0x27

LiquidCrystal_PCF8574 lcd(addr, cols, rows);     // create lcd object - with support of special characters

void setup()
{
  Wire.begin();
  lcd.init();                         // .begin()/.init() initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(F("Hello, world!"));
  lcd.setCursor(0, 1);
  lcd.print(F("123456789ä123456789ö123456789ü123456789ß"));   // the memory can store up to 40 characters per line
}

// this function will call the scrollDisplayLeft method in a specific period
void tickScroll()
{
  static uint32_t previousMillis = 0;
  const uint16_t interval = 500;
  if (millis() - previousMillis > interval)
  {
    lcd.scrollDisplayLeft();
    previousMillis = millis();
  }
}

void loop()
{
  tickScroll();    // call this function as often as possible in the loop
}
