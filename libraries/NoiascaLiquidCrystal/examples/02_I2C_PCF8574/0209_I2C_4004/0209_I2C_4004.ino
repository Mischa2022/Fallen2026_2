/*******************************************************************************
   Hello World I2Cexp

   Demo how to use a 4004 (40 character, 4 rows) display with a PCF8574

   open tasks:
   -

   Hardware:
   LCD with PCF8574 Backpack should be wired as follows:

   LCD          PCF8574
   --------------------------
   VSS    GND   GND
   VDD    5V    Vin
   V0           -             contrast - connect a poti to GND
   RS           P0 RS
   RW           GND
   E1           P2 EN
   E2           P1
   DB0          -
   DB1          -
   DB2          -
   DB3          -
   D4           P4 DB4
   D5           P5 DB5
   D6           P6 DB6
   D7           P7 DB7
   LEDA   GND   indirectly used with a NPN driven by P3
   LEDK   5V    5V

   by noiasca
   2021-08-16   tbd: hardware test (5060/544)
   2020-09-05   ok 5254/506
   *******************************************************************************/

#include <Wire.h>                      // needed for the I2C interface
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm/
#include <NoiascaHW/lcd_PCF8574.h>     // include the proper IO interface

const byte cols = 40;                  // columns/characters per row
const byte rows = 4;                   // how many rows
const byte addr = 0x27;                // set the LCD address to 0x3F or 0x27

// The GPIO order on PCF8574 starts is 0 to 7
const byte rs = 0;
//const byte rw = 255;                 // not used by library. You must connect RW to GND to enable write.
const byte en = 2;
const byte en2 = 1;                    // on common modules this pin is used for RW - so you can rewire this line to Enable2
const byte d4 = 4;                     // only four data pins are used in 4 bit mode
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 3;                     // on common modules pin 3 is used as driver for the backlight
const t_backlightPol blType = NEGATIVE;// set to either POSITIVE, NEGATIVE (or FAULTY if you have a fauly keypad shield)

LiquidCrystal_PCF8574_4004 lcd(addr, rs, en, en2, d4, d5, d6, d7, bl, blType, cols, rows);
//LiquidCrystal_PCF8574_4004 lcd(addr, rs, en, en2, d4, d5, d6, d7, bl, blType, cols, rows, convert_small);  // create lcd object - with different converter

void setup()
{
  Serial.begin(115200);
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  lcd.setCursor(1, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("αβμΣ°÷∞←→äöüßÄÖÜ");     // show some special character entered in UTF-8

  delay(1000);
  lcd.setCursor(0, 2);
  lcd.print("Noiasca 4004 - 2021");
  lcd.setCursor(0, 3);
  lcd.print("Powered by noiasca");
}

void demo2()
{
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}

void loop()
{
  // demo2();
}
