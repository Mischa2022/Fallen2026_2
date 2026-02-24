/*******************************************************************************
   Hello World I2C MCP23017

   LCD with MCP23017 - 16-Bit I/O Expander with I2C Interface

   Hardware:
   LCD with MCP23017 backpack can be wired as follows:

   LCD          MCP23017
   --------------------------
   VSS    GND   GND
   VDD    5V    Vin
   V0           -            contrast - connect to the wiper of a potentiometer, other legs to GND
   RS           GPIOB7
   RW           -            unused
   E            GPIOB5
   DB0          -
   DB1          -
   DB2          -
   DB3          -
   D4           GPIOB4
   D5           GPIOB3
   D6           GPIOB2
   D7           GPIOB1
   LEDA   GND   GPIOA7        Backlight circuitry (HIGH signal enables backlight using a simple NPN transistor)
   LEDK   5V

   Information:
   if you are using this sketch with an "LCD RGB KEYPAD For RPi" - the green LED will light

   by noiasca
   2021-05-16   base class 4708/504
   2021-04-18   base class 4686/503

   *******************************************************************************/

#include <Wire.h>
#include <NoiascaLiquidCrystal.h>      // use the library downloaded from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm
#include <NoiascaHW/lcd_MCP23017.h>    // include the proper IO interface

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x20;                // set the LCD address to 0x20
                                       
const byte rs = 7 + 8;                 // GPIOB7
const byte rw = 255;                   // not used 
const byte en = 5 + 8;                 // GPIOB5
const byte d4 = 4 + 8;                 // GPIOB4
const byte d5 = 3 + 8;                 // GPIOB3
const byte d6 = 2 + 8;                 // GPIOB2
const byte d7 = 1 + 8;                 // GPIOB1
const byte bl = 7;                     // GPIOA7; set to 255 if not used

LiquidCrystal_MCP23017_custompin lcd(addr, rs, rw, en, d4, d5, d6, d7, bl, POSITIVE, cols, rows);
//LiquidCrystal_MCP23017_custompin_base lcd(addr, rs, rw, en, d4, d5, d6, d7, bl, POSITIVE, cols, rows); // this is just for internal tests

void setup()
{
  Serial.begin(115200);
  Serial.println(F("\nStart"));
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  //lcd.noBacklight();
  lcd.setCursor(1, 0);                 // set the cursor to a specific position
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("αβμΣ°÷∞←→äöüßÄÖÜ");       // show some special character entered in UTF-8
  if (rows > 2)
  {
    lcd.setCursor(0, 2);
    lcd.print("Noiasca MCP23017   ");
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
