/*******************************************************************************
   LCD Menu with Options - Hello World

   This is a class based menu for a LCD.

   The code supports a variable number of menu entries
   all lines of your LCD will be used (1, 2 or 4 lines)

   Hardware:
   LCD with PCF8574 port expander
   3 push buttons connected to GND (up, down and select)

   by noiasca
   2022-02-07   adopted as example for LCD library
   2022-01-24   based on a idea in https://forum.arduino.cc/t/menu-mit-20x4-lcd-funktioniert-nicht-richtig/883443/37

   *******************************************************************************/

#include <Wire.h>                      // needed for LCD with PCF8574 port expander
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 
#include <NoiascaHW/lcd_PCF8574.h>     // include the proper IO interface
constexpr byte cols = 16;              // columns/characters per row
constexpr byte rows = 2;               // how many rows
constexpr byte addr = 0x3F;            // set the LCD address to 0x3F or 0x27
LiquidCrystal_PCF8574 lcd(addr, cols, rows);               // create lcd object - with support of special characters

// this example uses buttons to navigate through the menu
constexpr byte upButton = A0;
constexpr byte downButton = A1;
constexpr byte backButton = A2;
constexpr byte selectButton = A3;

// prototype

void action0(byte, byte, byte, int);
void action1(byte, byte, byte, int);
void action2(byte, byte, byte, int);
void action3(byte, byte, byte, int);
void action4(byte, byte, byte, int);
void action5(byte, byte, byte, int);
void action6(byte, byte, byte, int);
void action7(byte, byte, byte, int);
void back(byte, byte, byte, int);

#include <NoiascaMenu.h>
//each menu line needs an prompter (text to be displayed) and a function will should be called

//const char theString[] PROGMEM ="Option F";  // https://forum.arduino.cc/t/progmem-and-class-constructor/346118/3

MenuLine menu0line0("Option A", action0);
MenuLine menu0line1("Option B s1", action1);
MenuLine menu0line2("Option C s2", action2);
MenuLine menu0line3("Option D s3", action3);
MenuLine menu0line4("Option E", action4);
MenuLine menu0line5("Option F", action5);

MenuLine menuLineOnOff0("Off", action5);
MenuLine menuLineOnOff1("On", action5);

MenuLine menuLineRGB0("red", action6);
MenuLine menuLineRGB1("green", action6);
MenuLine menuLineRGB2("blue", action6);

MenuLine menuLineSpeed0("slow", action6);
MenuLine menuLineSpeed1("medium", action6);
MenuLine menuLineSpeed2("fast", action6);
MenuLine menuLineBack("(return)", back);
MenuLine menuLineNothing("nothing");

// menu screens are collection of several lines:
MenuScreen menuScreenMain(&menu0line0, &menu0line1, &menu0line2, &menu0line3, &menu0line4, &menu0line5);
MenuScreen menuScreenOnOff(&menuLineOnOff0, &menuLineOnOff1);
MenuScreen menuScreenRGB(&menuLineRGB0, &menuLineRGB1, &menuLineRGB2);
MenuScreen menuScreenSpeed(&menuLineSpeed0, &menuLineSpeed1, &menuLineSpeed2, &menuLineNothing, &menuLineBack);            // example of screen with exit/back/return
// menu system is the collection of several menu screens:
MenuSystem<LiquidCrystal_PCF8574> menuSystem(lcd, rows, &menuScreenMain, &menuScreenOnOff, &menuScreenRGB, &menuScreenSpeed);

// besser wäre etwas ala "ID" und "option"

void action0(byte screen, byte id, byte line, int value)                       // do what ever is needed
{
  Serial.println(F("action0"));
  (void)screen;  // if you don't use the screen, avoid warning for unused varialbe
  (void)id;
  (void)line;
  (void)value;

  lcd.clear();
  lcd.print("-Executing A");
  delay(1500);
  menuSystem.screen = 0;
  menuSystem.show();
}

//switch to menuScreen 1
void action1(byte screen, byte id, byte line, int value)
{
  Serial.println(F("action1"));
  (void)screen;
  (void)id;
  (void)line;
  (void)value;
  menuSystem.setId(menuSystem.getLine()); // preserve former line into id
  menuSystem.setScreen(1);

  menuSystem.show();
}

//switch to menuScreen 2
void action2(byte screen, byte id, byte line, int value)
{
  Serial.println(F("action2"));
  (void)screen;
  (void)id;
  (void)line;
  (void)value;
  menuSystem.setId(menuSystem.getLine());  // preserve former screen into id
  menuSystem.setScreen(2);
  menuSystem.show();
}

void action3(byte screen, byte id, byte line, int value)
{
  Serial.println(F("action3"));
  (void)screen;
  (void)id;
  (void)line;
  (void)value;
  menuSystem.setId(menuSystem.getLine());// preserve former screen into id
  menuSystem.setScreen(3);
  menuSystem.show();
}

void action4(byte screen, byte id, byte line, int value)
{
  Serial.println(F("action4"));
  (void)screen;
  (void)id;
  (void)line;
  (void)value;
  lcd.clear();
  lcd.print(F("-Executing E"));
  delay(1500);
  menuSystem.setLine(4);
  menuSystem.setScreen(0);
  menuSystem.show();
}

void action5(byte screen, byte id, byte line, int value)
{
  Serial.print(F("Action5 "));
  Serial.print(F(" screen=")); Serial.print(screen);
  Serial.print(F(" id=")); Serial.print(id);
  Serial.print(F(" line=")); Serial.print(line);
  Serial.print(F(" value=")); Serial.println(value);
  lcd.clear();
  lcd.print(F("-Executing F"));
  delay(1500);
  menuSystem.setLine(5);
  menuSystem.setScreen(0);
  menuSystem.setId(0);
  menuSystem.show();
}

void action6(byte screen, byte id, byte line, int value)
{
  Serial.print(F("Action6 "));
  Serial.print(F(" screen=")); Serial.print(screen);
  Serial.print(F(" id=")); Serial.print(id);
  Serial.print(F(" line=")); Serial.print(line);
  Serial.print(F(" value=")); Serial.println(value);
  lcd.clear();
  lcd.print("-Executing G");
  delay(1500);
  menuSystem.setLine(6);
  menuSystem.setScreen(0);
  menuSystem.setId(0);
  menuSystem.show();
}

void action7(byte screen, byte id, byte line, int value)
{
  Serial.println(F("action7"));
  (void)screen;
  (void)id;
  (void)line;
  (void)value;
  lcd.clear();
  lcd.print("-Executing #7");
  delay(1500);
  menuSystem.setLine(7);
  menuSystem.setScreen(0);
  menuSystem.setId(0);
  menuSystem.show();
}

void action8(byte screen, byte id, byte line, int value)
{
  Serial.println(F("action8"));
  (void)screen;
  (void)id;
  (void)line;
  (void)value;
  lcd.clear();
  lcd.print(F("-Executing #8"));
  delay(1500);
  menuSystem.setScreen(0);
  menuSystem.setId(0);
  menuSystem.show();
}

void back(byte screen, byte id, byte line, int value)
{
  Serial.println(F("back"));
  (void)screen;
  (void)id;
  (void)line;
  (void)value;
  menuSystem.cursorBack();
}

void readButton()
{
  if (digitalRead(downButton) == LOW) {
    menuSystem.cursorDown();
    delay(100);                        // dirty delay to debounce button
    while (!digitalRead(downButton));  // wait for button release
  }

  if (digitalRead(upButton) == LOW) {
    menuSystem.cursorUp();
    delay(100);                        // dirty delay to debounce button
    while (!digitalRead(upButton));
  }

  if (digitalRead(backButton) == LOW) {
    menuSystem.cursorBack();
    delay(100);                        // dirty delay to debounce button
    while (!digitalRead(backButton));
  }

  if (digitalRead(selectButton) == LOW) {
    menuSystem.activate();             // activate the current line
    delay(100);                        // dirty delay to debounce button
    while (!digitalRead(selectButton));
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Simple Class based menu"));
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(backButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  menuSystem.show();
}

void loop()
{
  readButton();
}
