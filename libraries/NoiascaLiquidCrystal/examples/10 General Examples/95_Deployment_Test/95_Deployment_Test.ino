/*******************************************************************************
   Deployment Test
   Testsketch to demostrate several displays
   Compiles several HW implementations

   When all LCDs on my testboard are working, the library can be distributed.

   parallel 4bit

   I2C
   - PCF8574 Expander
   - MCP23017 Expander
   - Native OLED
   - Native RGB

   SPI
   - MCP23S08

   todo 
    - 4004

   by noiasca
   2021-08-16  6 displays 11748/712
   2021-08-10  6 displays 11670/705

*******************************************************************************/
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows

#define FONT 3                         // the OLED supports font 0 English - Japanese; 1 Western European I; 2 English - Russian; 3 Western European II (e.g. for German)

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

#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit
LiquidCrystal_4bit lcd(8, 9, 4, 5, 6, 7, 255, cols, rows);  // create lcd object

#include <Wire.h>
#include <NoiascaHW/lcd_PCF8574.h>     // I2C PCF8574 Standard Backpack
LiquidCrystal_PCF8574 lcd_PCF8574(0x27, cols, rows);

#include <NoiascaHW/lcd_MCP23017.h>    // include the proper IO interface
const byte rs = 7 + 8;                 // GPIOB7 (bit 7 on Port B therefore 7 + 8)
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

LiquidCrystal_MCP23017_custompin lcd_MCP23017(0x20, rs, rw, en, d4, d5, d6, d7, bl, POSITIVE, cols, rows);

#include <NoiascaHW/lcd_wire.h>        // the native I2C interface (NO expander!). Connect SDA to LCD-Pin 8 and SCL to LCD-Pin 7
LiquidCrystal_Wire_RGB lcd_RGB(0x3E, cols, rows);           // create lcd object for a Sureeno RGB display

LiquidCrystal_Wire lcd_OLED(0x3c, cols, rows, MYCONVERT);               // create lcd object for a OLED display

#include <SPI.h>
#include <NoiascaHW/lcd_MCP23S08.h>    // SPI MCP23S08
LiquidCrystal_MCP23S08 lcd_MCP23S08(0x40, 5, cols, rows, convert_SPLC780D1_003A);

void setup()
{
  Serial.begin(115200);
  Serial.println(F("LCD User Acceptance Test"));

  Wire.begin();                        // used for PCF8574, MCP23017 and displays with native I2C interface (OLED LEC1621, Sureeno, Grove)
  SPI.begin();                         // used for MCP23S08

  lcd.begin();                         // initialize the LCD
  lcd.backlight();
  lcd.print(F("LCD 4bit  äÄ°"));

  lcd_PCF8574.begin();
  lcd_PCF8574.backlight();
  lcd_PCF8574.print(F("PCF8574 äÄ°"));

  lcd_MCP23017.begin();
  lcd_MCP23017.backlight();
  lcd_MCP23017.print(F("MCP23017 äÄ°"));
  for (auto & i : button) lcd_MCP23017.setPinMode(i, INPUT_PULLUP);   // activate the internal pullups for the defined buttons
  lcd_MCP23017.setPinMode(rgbBlue, OUTPUT);     // set the RGB pin to output
  lcd_MCP23017.setPinMode(rgbRed, OUTPUT);
  lcd_MCP23017.setPinMode(rgbGreen, OUTPUT);

  lcd_RGB.begin();
  lcd_RGB.backlight();
  lcd_RGB.setRGB(255, 255, 0);
  lcd_RGB.print(F("RGB äÄ°"));

  lcd_OLED.begin();                         // initialize the LCD
  lcd_OLED.setFont(FONT);                   // at the beginning define your font
  lcd_OLED.print(F("LEC1621 font="));
  lcd_OLED.print(FONT);
  lcd_OLED.setCursor(0, 1);
#if FONT == 2                               // Demo print according to your font configuration
  lcd_OLED.print(F("УуФфЦцЧч äÄöÖüÜß"));       // Russian European Example
#else
  lcd_OLED.print(F("αβμΣ°÷∞←→äöüßÄÖÜ"));      // show some special character entered in UTF-8
#endif

  lcd_MCP23S08.begin();                     // initialize the LCD
  lcd_MCP23S08.backlight();
  lcd_MCP23S08.print(F("MCP23S08 äÄ°"));

  delay(1000);
  // show off some color on the RPi Keypad
  lcd_MCP23017.digitalWrite(rgbBlue, HIGH);      // swith a RGB pin
  delay(500);
  lcd_MCP23017.digitalWrite(rgbRed, HIGH);
  delay(500);
  lcd_MCP23017.digitalWrite(rgbGreen, HIGH);

  // show off some color on the RGB display 
  lcd_RGB.setRGB(0, 255, 0);
  Serial.println(F("end setup()"));
}

void demoMillis()
{
  static uint32_t previousMillis = 0;
  if (millis() - previousMillis > 3000)
  {
    lcd.setCursor(0, 1); lcd.print(millis()); lcd.print(" ");
    lcd_MCP23S08.setCursor(0, 1); lcd_MCP23S08.print(millis()); lcd_MCP23S08.print(" ");
    lcd_MCP23017.setCursor(0, 1); lcd_MCP23017.print(millis()); lcd_MCP23017.print(" ");
    lcd_RGB.setCursor(0, 1); lcd_RGB.print(millis()); lcd_RGB.print(" ");
    lcd_PCF8574.setCursor(0, 1); lcd_PCF8574.print(millis()); lcd_PCF8574.print(" ");
    lcd_OLED.setCursor(0, 1); lcd_OLED.print(millis()); lcd_OLED.print(" ");
    previousMillis = millis();
  }
}

void runMCP23017()
{
  static uint32_t previousMillis;
  static byte previousState[5];
  static bool backlightState = true;
  if (millis() - previousMillis > 50) // one debounce for all
  {
    byte buttonState = lcd_MCP23017.digitalRead(1);  // right button
    if (buttonState == LOW && previousState[1] == HIGH) 
    {
      Serial.println(F("new random color"));
      lcd_MCP23017.digitalWrite(rgbBlue, random(2));
      lcd_MCP23017.digitalWrite(rgbRed, random(2));
      lcd_MCP23017.digitalWrite(rgbGreen, random(2));
      lcd_RGB.setRGB(random(256), random(256), random(256));
    }
    previousState[1] = buttonState;

    buttonState = lcd_MCP23017.digitalRead(2);   // down button
    if (buttonState == LOW && previousState[2] == HIGH) 
    {
      backlightState = !backlightState;
      Serial.print (F("toggle backlight ")); Serial.println(backlightState);
      // the RPi keypad will be always on
      lcd_MCP23S08.setBacklight(backlightState);
      lcd_PCF8574.setBacklight(backlightState);
      lcd_MCP23017.setBacklight(backlightState); 
      backlightState == true ? lcd_RGB.backlight() : lcd_RGB.noBacklight(); // setBacklight is used for brigthness control, therefore we use backlight/noBacklight
    }
    previousState[2] = buttonState;
  }
}

void loop()
{
  demoMillis();
  runMCP23017();
}
