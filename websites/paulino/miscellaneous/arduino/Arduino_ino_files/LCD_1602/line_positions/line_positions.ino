//counts the positins in one LCD line
//2024.8.26
 
#include <LiquidCrystal.h>// include the library code
/**********************************************************/
char array1[]="Line 1              ";  //the string to print on the LCD
char array2[]="Line 2              ";  //the string to print on the LCD
char array3[]="Line 3              ";  //the string to print on the LCD
char array4[]="Line 4              ";  //the string to print on the LCD

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 6,7, 8, 9, 10);
/*********************************************************/

void setup()
{
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows: 
}
/*********************************************************/

void loop() 
{
    
    lcd.print(array1);  // Print a message to the LCD.
    lcd.print(array2);  // Print a message to the LCD.
    lcd.print(array3);  // Print a message to the LCD.
    lcd.print(array4);  // Print a message to the LCD.
    delay(5000);  //wait for 5s
    lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.

  
}
/************************************************************/
