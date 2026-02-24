/*******************************************************************************
   Simple LCD Menu

   This is a simple menu for your LCD. 
   
   For sure there are more sophistaced solutions out there, 
   but if you just need several menu items, this example
   can give you an idea how to program a menu.

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
constexpr byte selectButton = A3;

byte menu = 0;                         // the actual selected menu entry
const char *entry[]                    // the Menu entries to be displayed on the LCD
{
  "Menu Item A",
  "Menu Item B", 
  "Menu Item C", 
  "Menu Item D", 
  "Menu Item E", 
  "Menu Item F", 
  "Menu Item G"
};
const size_t noOfEntries = sizeof(entry) / sizeof(entry[0]);         // calculate the number of menu entries

void readButton()
{
  if (!digitalRead(downButton)) {
    if (menu < noOfEntries - 1) menu++;// stop down button at the last menu entry
    updateMenu();
    delay(100);                        // dirty delay to debounce button
    while (!digitalRead(downButton));  // wait for button release
  }

  if (!digitalRead(upButton)) {
    if (menu > 0) menu--;              // stop up button at the first menu entry
    updateMenu();
    delay(100);                        // dirty delay to debounce button
    while (!digitalRead(upButton));
  }
  if (!digitalRead(selectButton)) {
    executeAction();
    updateMenu();
    delay(100);                        // dirty delay to debounce button
    while (!digitalRead(selectButton));
  }
}

void updateMenu()                      // displays the Menu and marks the actual entry
{
  lcd.clear();
  byte from = 0;
  from = (menu / rows) * rows;         // the first entry on the LCD is calculated depending on the available LCD rows and the current entry
  byte to = from + rows - 1;           // the last entry depends on the available rows on the LCD
  byte rowActual = 0;
  for (byte i = from; i <= to; i++)
  {
    lcd.setCursor(0, rowActual);
    if (i == menu) lcd.write('>');     // marker to indicate the actual menu entry
    lcd.setCursor(1, rowActual);
    lcd.print(entry[i]);
    rowActual++;
  }
}

void executeAction()                   // this function calls the different actions
{
  switch (menu) {
    case 0:
      action0();
      break;
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
    case 5:
      action5();
      break;
    case 6:
      action6();
      break;
    case 7:
      action7();
      break;
  }
}

void action0()                         // do what ever is needed
{
  lcd.clear();
  lcd.print("-Executing A");
  delay(1500);
}

void action1()
{
  lcd.clear();
  lcd.print("-Executing B");
  delay(1500);
}

void action2()
{
  lcd.clear();
  lcd.print("-Executing C");
  delay(1500);
}

void action3()
{
  lcd.clear();
  lcd.print("-Executing D");
  delay(1500);
}

void action4()
{
  lcd.clear();
  lcd.print("-Executing E");
  delay(1500);
}
void action5()

{
  lcd.clear();
  lcd.print("-Executing F");
  delay(1500);
}

void action6()
{
  lcd.clear();
  lcd.print("-Executing G");
  delay(1500);
}

void action7()
{
  lcd.clear();
  lcd.print("-Executing #7");
  delay(1500);
}

void action8()
{
  lcd.clear();
  lcd.print("-Executing #8");
  delay(1500);
}

void setup()
{
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  updateMenu();
}

void loop()
{
  readButton();
}
