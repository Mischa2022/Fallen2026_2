/*******************************************************************************
   Hello World I2Cexp

   LCD with PCF8574 - 8-Bit I/O Expander with I2C Interface

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
   2021-08-24   base class 3302/317
   2021-05-16   base class 3300/317
   2020-09-05   base class 3530/319
   2022-06-23   base class 3384/327
   *******************************************************************************/

   #include <Wire.h>                   // needed for the I2C interface
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 
#include <NoiascaHW/lcd_PCF8574.h>     // include the proper IO interface

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x3F;                // set the LCD address to 0x3F or 0x27

LiquidCrystal_PCF8574 lcd(Wire, addr, cols, rows);               // create lcd object - with support of special characters

void setup()
{
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  lcd.setCursor(1, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("αβμΣ°÷∞←→äöüßÄÖÜ");     // show some special character entered in UTF-8
  if (rows > 2)
  {
    lcd.setCursor(0, 2);
    lcd.print("Noiasca LC I2C 2022");
    lcd.setCursor(2, 3);
    lcd.print("Powered by noiasca");
  }
}

void loop()
{
 /*
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print(millis()/1000);
 */
}
