/*******************************************************************************
   Convert Descender
   converts the small letters with decenders (g, j, p, q and y) 
   custom made characters which use the lowest line but not exceed the size of
   small letters.

   call the converter_custom to use up to 8 special characters for your language
   including UTF-8 multi byte characters

   Important: You have to chose the proper hardware interface in the sketch!

   by noiasca
   2021-09-06 use convert_custom
   2021-08-21 OK (4320/339)
   
 *******************************************************************************/
#include <NoiascaLiquidCrystal.h>                // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm
#include <utility/NoiascaCustomCharacters.h>     // file with several predefined custom characters

const byte cols = 16;                            // columns/characters per row
const byte rows = 2;                             // how many rows

// activate the needed lines according to your LCD hardware
#define HARDWARE 2                               // 1 parallel; 2 pcf8574; 5 native I2C; 6 MCP23S08

#if HARDWARE == 1
#include <NoiascaHW/lcd_4bit.h>                  // parallel interface, 4bit
const byte rs = 8;
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;                            // set to 255 if not used
LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, convert_custom);  // create lcd object parallel 4bit
#endif

#if HARDWARE == 2
#include <Wire.h>
#include <NoiascaHW/lcd_PCF8574.h>             // I2C PCF8574 expander
const byte addr = 0x27;
LiquidCrystal_PCF8574 lcd(addr, cols, rows, convert_custom);         // create lcd object I2C
#endif

#if HARDWARE == 6
#include <SPI.h>
#include <NoiascaHW/lcd_MCP23S08.h>            // SPI MCP23S08 expander
const byte csPin = 5;                          
LiquidCrystal_MCP23S08 lcd(0x40, csPin, cols, rows, convert_custom); // create lcd object SPI
#endif

void customCharacterMapping_local()
{
  //  This UTF8 code will become  -->   that custom character
  utf8_to_customChar[0] = 'g';    lcd.createChar_P(0, latin_small_g_descender);  // variants predefined in the library
  utf8_to_customChar[1] = 'j';    lcd.createChar_P(1, latin_small_j_descender);
  utf8_to_customChar[2] = 'p';    lcd.createChar_P(2, latin_small_p_descender);
  utf8_to_customChar[3] = 'q';    lcd.createChar_P(3, latin_small_q_descender);
  utf8_to_customChar[4] = 'y';    lcd.createChar_P(4, latin_small_y_descender);
  utf8_to_customChar[5] = 0xC384; lcd.createChar_P(5, latin_capital_a_diareses); // Ä predefined in the library
  utf8_to_customChar[6] = 0xc396; lcd.createChar_P(6, latin_capital_o_diareses); // Ö predefined in the library
  utf8_to_customChar[7] = 0xc39c; lcd.createChar_P(7, latin_capital_u_diareses); // Ü predefined in the library
}

void setup()
{
#if HARDWARE >= 2 && HARDWARE <= 5     // start communication bus depending on your hardware
  Wire.begin();                        // start the I2C bus
#endif
#if HARDWARE == 6
  SPI.begin();                         // start the SPI bus
#endif

  lcd.begin();                         // initialize the lcd
  lcd.backlight();
  customCharacterMapping_local();
  
  lcd.setCursor(0, 0);
  lcd.print("agcjepnqmy");
  lcd.setCursor(0, 1);
  lcd.print("Ä ä Ö ö Ü ü ß µ°");       // small ä, ö, ü are available in the standard ROM
}

void loop()
{}
