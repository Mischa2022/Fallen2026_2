/*******************************************************************************
   Individual Converter 
   example how to use different UTF8 converter variants from the library

   Hardware:
   LCD with MCP23S08 - 8-Bit I/O Expander with Serial Interface (SPI)
   As the MCP23S08 only offers 8 pins and we need RS RW EN - only 4bit mode can be used.
   the remaining pin (P3) will be used for backlight control.

   open tasks:

   by noiasca
   2021-06-26

 *******************************************************************************/

#include <SPI.h>
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 
#include <NoiascaHW/lcd_MCP23S08.h>    // include the proper HW interface

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x40;                // though SPI, the MCP23S08 has two additional adress pins. Use 0x40 if A0 and A1 are connected to GND
const byte csPin = 5;                  // the CS PIN for the MCP23S08 IC

LiquidCrystal_MCP23S08 lcd(addr, csPin, cols, rows);                     // use the standard converter (Ä gets converted to A) from library
// as alternative you can hand over several converters to the constructor
//LiquidCrystal_MCP23S08 lcd(addr, csPin, cols, rows, convert_ae);       // a converter (Ä gets converted to Ae) from library
//LiquidCrystal_MCP23S08 lcd(addr, csPin, cols, rows, convert_small);    // a converter (Ä gets converted to ä) from library
//LiquidCrystal_MCP23S08 lcd(addr, csPin, cols, rows, convert_special);  // a converter (Ä gets converted to ä) from library - not ready yet
//LiquidCrystal_MCP23S08 lcd(addr, csPin, cols, rows, convert_SPLC780D1_003A);  // a converter for the european SPLC780D1 003A (Ä gets converted to Ä)


void setup()
{
  SPI.begin();                         // start SPI
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  lcd.createUml();                     // create 3 German Umlauts using Special Characters 5, 6, and 7 - used for convert_special
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("Ä Ö Ü ä ö ü ß °");
}

void loop()
{}
