/*******************************************************************************
   OLED LEC1621 HelloWorld
   Strandtest for the OLED LEC1621

   by noiasca
   2021-05-16

*******************************************************************************/

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows

#include <Wire.h>
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 
#include <NoiascaHW/lcd_wire.h>        // the native I2C interface (NO expander!). Connect SDA to LCD-Pin 8 and SCL to LCD-Pin 7
LiquidCrystal_Wire lcd(0x3c, cols, rows, convert_LEC1621_01);               // create lcd object for a OLED display

//#include <NoiascaHW/lcd_PCF8574.h>   // include the Hardware Interface: I2C PCF8574
//const byte addr = 0x27;
//LiquidCrystal_PCF8574 lcd(addr, cols, rows, convert_LEC1621_01 );

//#include <NoiascaHW/lcd_MCP23S08.h>  // include the Hardware Interface: SPI MCP23S08
//const byte csPin = 10;                    
//LiquidCrystal_MCP23S08 lcd(0x40, csPin, cols, rows, convert_LEC1621_01);

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  //SPI.begin();                       // include either SPI or I2C depending on your hardware

  lcd.begin();                         // initialize the LCD
  lcd.setFont(1);                      // at the beginning define your font
  lcd.setCursor(1, 0);
  lcd.print("Hello, world! ");
  lcd.setCursor(0, 1);
  lcd.print("αβμΣ°÷∞←→äöüßÄÖÜ");       // show some special character entered in UTF-8
}

void loop()
{}
