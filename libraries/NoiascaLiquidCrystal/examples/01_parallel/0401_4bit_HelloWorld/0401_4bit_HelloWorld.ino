/*******************************************************************************
   Hello World
   LCD in parallel 4 bit mode

   Hardware:
   LCD should be wired as follows:

   LCD          UNO
   --------------------------
   VSS   GND    GND
   VDD   5V     5V
   V0           -   contrast - connect a poti to GND, around 2K7
   RS           P8  RS
   RW    GND    -   Read/Write not used in this library - Pulldown to GND
   E            P9  Enable
   D0           -   not used in 4bit mode
   D1           -   not used in 4bit mode
   D2           -   not used in 4bit mode
   D3           -   not used in 4bit mode
   D4           P4  DB4
   D5           P5  DB5
   D6           P6  DB6
   D7           P7  DB7
   LEDA   5V
   LEDK   GND   P10 Backlight circuitry (HIGH signal enables backlight using a simple NPN transistor)
   
   by noiasca
   2021-08-14 base 4bit 1726/109
   2021-05-16 base 4bit 1672/104
   2021-04-05 base 4bit 2052/114
   2021-03-13 base 4bit 1898/107
   2021-01-06 base 4bit 2250/109
   
*******************************************************************************/

#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 
#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte rs = 8;
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;                    // set to 255 if not used

LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows);  // create lcd object
//LiquidCrystal_4bit_base lcd(rs, en, d4, d5, d6, d7, bl, cols, rows);  // base class without UTF-8

void setup()
{
  lcd.begin();                         // initialize the LCD
//  lcd.setBacklightNegative();        // use this if you need to invert the on/off behaviour of the backlight
  lcd.backlight();                     // turn on backlight
  lcd.setCursor(2, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("αβμΣ°÷∞←→äöüßÄÖÜ");     // show some special character entered in UTF-8
  if (rows > 2)
  {
    lcd.setCursor(0, 2);
    lcd.print("Noiasca LC 4bi 2021");
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
    lcd.print("                ");
  */
}
