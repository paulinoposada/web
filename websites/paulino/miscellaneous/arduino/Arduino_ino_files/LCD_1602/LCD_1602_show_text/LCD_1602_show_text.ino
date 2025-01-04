//shows a text on the LCD
//2024.8.26
 
#include <LiquidCrystal.h>// include the library code
/**********************************************************/
char array1[]="Test";  //the string to print on the LCD

int tim = 10000;  //the value of delay time
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 6, 7, 8, 9, 10);
/*********************************************************/

void setup()
{
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows: 
}
/*********************************************************/

void loop() 
{
    lcd.setCursor(15,0);  // set the cursor to column 15, line 0
    lcd.print(array1);  // Print a message to the LCD.
      delay(tim);  //wait for 5s
    lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
    
    lcd.print(array1);  // Print a message to the LCD.
      delay(tim);  //wait for 5s
    lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
  
}
/************************************************************/
