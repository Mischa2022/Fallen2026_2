/*******************************************************************************
   LCD RGB KEYPAD FOR RPi

   Example for MCP23017 - 16-Bit I/O Expander with I2C Interface

   Hardware:
   "LCD RGB KEYPAD FOR RPi" is a module with MCP23017, 5 buttons and a RGB LED.
   The backlight on this board is always on and there is no connection to switch BL off.
   it differs slightly from the Adafruit Board.

   Where to buy:
   Aliexpress: https://s.click.aliexpress.com/e/_9Qzrvn
   Amazon: https://amzn.to/3wedyLZ

   The Sketch
   - prints some demo text on the screen
   - switches on the green RGB
   - reads the 5 buttons (0 if pressed)


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
   LEDA   GND   -            Backlight circuitry allways on
   LEDK   5V

   by noiasca
   2021-05-31   base class 5900/512 (includes some more code to display)
   2021-05-16   base class 5652/510
   2021-04-18   base class 4686/503

   *******************************************************************************/

#include <Wire.h>
#include <NoiascaLiquidCrystal.h>      // use the library downloaded from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm
#include <NoiascaHW/lcd_MCP23017.h>    // include the proper IO interface

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x20;                // set the LCD address (0x20 - 0x27)

const byte rs = 7 + 8;                 // GPIOB7   (bit 7 on Port B therefore 7 + 8)
const byte rw = 255;                   // not used
const byte en = 5 + 8;                 // GPIOB5
const byte d4 = 4 + 8;                 // GPIOB4
const byte d5 = 3 + 8;                 // GPIOB3
const byte d6 = 2 + 8;                 // GPIOB2
const byte d7 = 1 + 8;                 // GPIOB1
const byte bl = 255;                   // not used - the backlight on this shield is always on

const byte rgbRed = 6;                 // GPIOA6
const byte rgbGreen = 0 + 8;           // GPIOB0
const byte rgbBlue = 7;                // GPIOA7

const byte button[] {4, 3, 2, 1, 0};   // the 5 buttons on the LCD RGB KEYPAD connected to GPIO A
const byte OFF = HIGH;                 // the buttons on the board are low active, therefore inverse
const byte ON  = !OFF;

LiquidCrystal_MCP23017_custompin lcd(addr, rs, rw, en, d4, d5, d6, d7, bl, POSITIVE, cols, rows);
//LiquidCrystal_MCP23017_custompin_base lcd(addr, rs, rw, en, d4, d5, d6, d7, bl, POSITIVE, cols, rows); // this is just for internal tests

void setup()
{
  Serial.begin(115200);
  Serial.println(F("\nStart"));
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  lcd.setCursor(1, 0);                 // set the cursor to a specific position
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("αβμΣ°÷∞←→äöüßÄÖÜ");      // show some special character entered in UTF-8

  for (auto & i : button)
    lcd.setPinMode(i, INPUT_PULLUP);   // activate the internal pullups for the defined buttons
  lcd.setPinMode(rgbBlue, OUTPUT);     // set the RGB pin to output
  lcd.setPinMode(rgbRed, OUTPUT);
  lcd.setPinMode(rgbGreen, OUTPUT);
  lcd.digitalWrite(rgbBlue, OFF);      // swith a RGB pin
  lcd.digitalWrite(rgbRed, OFF);
  lcd.digitalWrite(rgbGreen, ON);
}

void loop()
{
  runInputs();
}

void runInputs()
{
  lcd.setCursor(0, 1);
  for (auto & i : button)
  {
    byte buttonState = lcd.digitalRead(i);
    Serial.print(buttonState);
    Serial.print("\t");
    lcd.print(buttonState);
    lcd.print(" ");
  }
  Serial.println();
  delay(500);      // dirty delay; slow down the sketch a little bit
}
