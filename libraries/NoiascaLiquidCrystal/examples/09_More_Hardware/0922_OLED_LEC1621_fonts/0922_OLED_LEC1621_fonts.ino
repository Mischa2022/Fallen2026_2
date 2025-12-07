/*******************************************************************************
   OLED LEC 1621
   Testsketch to demostrate the fonts on the OLED LEC1621

   This display can be used in parallel mode and therefore also with the well 
   known expanders (e.g. PCF8574).
   
   Additionally this OLED has native I2C support, but you must activate that 
   with solder jumpers on the backside of the LCD (short JIM1 & JIM0).
   See the datahseet of _your_ OLED to get it right.
   
   by noiasca
   2021-06-06

*******************************************************************************/
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows

#define FONT 2                         // the OLED supports font 0..3
//                                        0 English - Japanese
//                                        1 Western European
//                                        2 English - Russian
//                                        3 Western European II (e.g. for German)

#define HARDWARE 5                     // 1 pcf8574; 5 native I2C; 6 MCP23S08

/* End of configuration */

#if FONT == 0                          // OLED with font 0 English - Japanese uses the standard HD44780 A00 Converter
#define MYCONVERT convert
#elif FONT == 1                        // OLED with font 1 Western European
#define MYCONVERT convert_LEC1621_01
#elif FONT == 2                        // OLED with font 2 European Russian
#define MYCONVERT convert_LEC1621_02
#elif FONT == 3                        // OLED with font 3 Western – European II uses the SPLC780D1_003A converter
#define MYCONVERT convert_SPLC780D1_003A
#endif

/* Depending on your defines the compiler will chose the right cosntructor */
#if HARDWARE == 1
#include <Wire.h>
#include <NoiascaHW/lcd_PCF8574.h>     // I2C PCF8574 Standard Backpack
const byte addr = 0x27;                // set the LCD address to 0x3F or 0x27
LiquidCrystal_PCF8574 lcd(addr, cols, rows, MYCONVERT );

#elif HARDWARE == 5
#include <Wire.h>
#include <NoiascaHW/lcd_wire.h>        // the native I2C interface (NO expander!). Connect SDA to LCD-Pin 8 and SCL to LCD-Pin 7
const byte lcdAddr = 0x3c;             // check the LCD address with an I2C scanner
LiquidCrystal_Wire lcd(lcdAddr, cols, rows, MYCONVERT);               // create lcd object for a Sureeno RGB display

#elif HARDWARE == 6
#include <NoiascaHW/lcd_MCP23S08.h>    // SPI MCP23S08
const byte csPin = 10;                 // Chip Select Pin
const byte addr = 0x40;                // address
LiquidCrystal_MCP23S08 lcd(addr, csPin, cols, rows, MYCONVERT );
#endif

void setup()
{
  Serial.begin(115200);
#if HARDWARE == 1 || HARDWARE == 5
  Wire.begin();                        // start I2C library
#elif HARDWARE == 6
  SPI.begin();
#endif
  lcd.begin();                         // initialize the LCD
  //lcd.backlight();                   // The OLED doesn't have a backlight, so you don't need to call this
  lcd.setFont(FONT);                   // at the beginning define your font
  lcd.setCursor(1, 0);
  //delay(1000);
  lcd.print("LEC1621 font=");
  lcd.print(FONT);
  lcd.setCursor(0, 1);
  //delay(1000);
#if FONT == 2                          // Demo print according to your font configuration
  lcd.print("УуФфЦцЧч äÄöÖüÜß");       // Russian European Example
#else
  lcd.print("αβμΣ°÷∞←→äöüßÄÖÜ");      // show some special character entered in UTF-8
#endif
}

void loop()
{}
