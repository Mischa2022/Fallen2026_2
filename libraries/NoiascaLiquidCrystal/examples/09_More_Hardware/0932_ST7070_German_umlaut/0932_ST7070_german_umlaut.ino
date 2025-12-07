/*******************************************************************************
   Various Variants of German Umlauts

   Hardware:
   A ST7070 display with I2C PCF8574 LCD Backpack

   open tasks: 
   - ISO 8583 Latin 1 - 4  Characters on LCD with SPI connector

   Hardware:
   LCD with PCF8574 Backpack should be wired as follows:
   
   LCD          PCF8574
   --------------------------
   VSS    GND   GND
   VDD    5V    Vin
   V0           -             contrast - connect a poti to GND
   RS           P0 RS
   RW           P1 RW
   E            P2 EN
   DB0          -
   DB1          -
   DB2          -
   DB3          -
   D4           P4 DB4
   D5           P5 DB5
   D6           P6 DB6
   D7           P7 DB7
   LEDA   GND   P3 Backlight circuitry (HIGH signal enables backlight using a simple NPN transistor)
   LEDK   5V

   by noiasca
   2021-05-16 UNTESTED Hardware
   2020-09-01

 *******************************************************************************/

#include <Wire.h>
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 
#include <NoiascaHW/lcd_PCF8574.h>     // include the proper IO interface

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x3F;                // most common LCD addresses are 0x3F or 0x27

// For the ST7070 display two converters are available

LiquidCrystal_PCF8574 lcd(addr, cols, rows, convert_ST7070);         // The standard constructor handles Latin-1 only
//LiquidCrystal_PCF8574 lcd(addr, cols, rows, convert_ST7070_ext);   // The extended constructor handles additional characters from Latin-2, Latin-3 and Latin-4

void setup()
{
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("Ä Ö Ü ä ö ü ß");
}

void loop()
{}
