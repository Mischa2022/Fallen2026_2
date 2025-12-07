/*******************************************************************************
   Fast I2C PCF8574 Interface
   
   Compare the PCF8574_fast with other implementations

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

   Dependencies:
   - Noiasca Buffer Print: download library from https://werner.rothschopf.net/microcontroller/202111_arduino_bufferprint.htm 

   by noiasca
   2022-03-06

 *******************************************************************************/

#include <Wire.h>
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x3F;                // set the LCD address to 0x3F or 0x27

// you can run several tests:


// fastest option without UTF-8 support                      // 16char  8char  1char in µs
#include <NoiascaLiquidCrystal.h>       
#include <NoiascaHW/lcd_PCF8574_fast.h>
LiquidCrystal_PCF8574_fast_base lcd(addr, cols, rows);        // 7028  / 3608 / 588 

/*
// UTF-8 support will add a slight overhead 
#include <NoiascaLiquidCrystal.h>       
#include <NoiascaHW/lcd_PCF8574_fast.h>
LiquidCrystal_PCF8574_fast lcd(addr, cols, rows);             // 7184 / 3672 / 600  
*/
/*
// default library incl. UTF-8 support
#include <NoiascaLiquidCrystal.h>       
#include <NoiascaHW/lcd_PCF8574.h>
LiquidCrystal_PCF8574 lcd(addr, cols, rows);                  // 11488 / 5756 / 724
*/

/*
// LiquidCrystal I2C version 1.1.2 without UTF-8 support
#include <LiquidCrystal_I2C.h>       
LiquidCrystal_I2C lcd(addr, cols, rows);                      // 23828 / 11892 / 1496
*/

/*
// and just as reminder, 
// I2C _is_ slow compared to other methods
#include <NoiascaLiquidCrystal.h>      
#include <NoiascaHW/lcd_4bit.h>  // parallel interface, 4bit
LiquidCrystal_4bit lcd(8, 9, 4, 5, 6, 7, 10, POSITIVE, 16, 2); // 1764 / 888 / 120
*/

void testSequence()
{
  uint32_t start, end;
  lcd.setCursor(0, 0);
  start = micros();
  lcd.print("1234567890123456");
  end = micros();
  Serial.println(end - start);
  lcd.setCursor(0, 1);
  lcd.print(end - start);

  lcd.setCursor(0, 0);
  start = micros();
  lcd.print("12345678");
  end = micros();
  Serial.println(end - start);
  lcd.setCursor(6, 1);
  lcd.print(end - start);
  
  lcd.setCursor(0, 0);
  start = micros();
  lcd.print("1");
  end = micros();
  Serial.println(end - start);
  lcd.setCursor(12, 1);
  lcd.print(end - start);
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();                        // start I2C library
  lcd.init();                          // initialize the LCD - for Noiasca libraries use .begin() instead! Other libraries might need init
 
  lcd.backlight();                     // turn on backlight
  lcd.setCursor(2, 0);
  lcd.print("PCF8574 fast - speed test");
  delay(2000);
  testSequence();
}

void loop()
{}
