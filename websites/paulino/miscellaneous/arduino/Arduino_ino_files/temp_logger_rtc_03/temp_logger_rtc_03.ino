  
/*
 * Temperature logger with 
 * 5 temperature sensors DS18B20
 * SD card module from lctech (www.lctech-inc.com)
 * rtc module DS1307
 * LCD
 */


#include <OneWire.h>               // temp sensor DS18B20 library
#include <DallasTemperature.h>     // temp sensor DS18B20 library

#include <SPI.h>                   // SD card module library
#include <SD.h>                    // SD card module library    

#include <RTClib.h>               // RCT module library

#include <LiquidCrystal.h>        // include the library code



RTC_DS1307 rtc;


File dataLog;
boolean sd_ok = 0;


// DS18B20 temp sensor data wire is conntec to the Arduino digital pin 2
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// LCD - initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 6,7, 8, 9, 10);


void setup() {
  
  // open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.print("Initializing SD card...");


  // initialize the SD card
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) 
  {
    Serial.println("initialization failed!");
    while (1);

  }
  else 
  {   // initialization OK
    sd_ok = 1;
    Serial.println("initialization done.");
    if( SD.exists("Log.txt") == 0 )   // test if file with name 'Log.txt' already exists
    {  // create a text file named 'Log.txt'
      Serial.print("\r\nCreate 'Log.txt' file ... ");
      dataLog = SD.open("Log.txt", FILE_WRITE);   // create (&open) file Log.txt
      if(dataLog) {                               // if the file opened okay, write to it:
        Serial.println("OK");
        dataLog.close();   // close the file
      }
      else
        Serial.println("error creating file.");
    }
  }
 


 // SETUP RTC MODULE
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }

  // automatically sets the RTC to the date & time on PC this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // manually sets the RTC with an explicit date & time, for example to set
  // January 21, 2021 at 3am you would call:
  // rtc.adjust(DateTime(2021, 1, 21, 3, 0, 0));



 // SETUP LCD MODULE
 lcd.begin(16, 2);  // set up the LCD's number of columns and rows:


}


  


void loop() 
{
  
    // Sets DateTime using the RTC
    DateTime now = rtc.now();
      
  
    // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
    sensors.requestTemperatures(); 


    // print date & time on PC serial monitor
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");

    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);

    // print data on PC serial monitor
    Serial.print("sensor 0 = ");
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print(" -- sensor 1 = ");
    Serial.print(sensors.getTempCByIndex(1));
    Serial.print(" -- sensor 2 = "); 
    Serial.print(sensors.getTempCByIndex(2));
    Serial.print(" -- sensor 3 = "); 
    Serial.print(sensors.getTempCByIndex(3));
    Serial.print(" -- sensor 4 = "); 
    Serial.println(sensors.getTempCByIndex(4));
            
    
    // write data to SD card
    if(sd_ok)
    {  // if the SD card was successfully initialized
      // open Log.txt file with write permission
      dataLog = SD.open("Log.txt", FILE_WRITE);
      
      // insert date & time in PC data file
 
      dataLog.print(now.year(), DEC);
      dataLog.print('/');
      dataLog.print(now.month(), DEC);
      dataLog.print('/');
      dataLog.print(now.day(), DEC);
      dataLog.print(';');
      dataLog.print(now.hour(), DEC);
      dataLog.print(':');
      dataLog.print(now.minute(), DEC);
      dataLog.print(':');
      dataLog.print(now.second(), DEC);
      dataLog.print(';');

      // insert data in data file
      dataLog.print( sensors.getTempCByIndex(0) );
      dataLog.print(";");
      dataLog.print( sensors.getTempCByIndex(1) );
      dataLog.print(";");      
      dataLog.print( sensors.getTempCByIndex(2) );
      dataLog.print(";");      
      dataLog.print( sensors.getTempCByIndex(3) );
      dataLog.print(";");      
      dataLog.println( sensors.getTempCByIndex(4) );
      dataLog.close();   // close the file
    }



      // show date & time and data data on LCD
    
    lcd.print(now.hour(), DEC);                  // Print hour to the LCD.
    lcd.print(':');                              // Print text to the LCD.
    lcd.print(now.minute(), DEC);                // Print minute to the LCD.
    lcd.print("                S1: ");           // Print text to the LCD.
    lcd.print(sensors.getTempCByIndex(0));       // Print sensor 0 value to the LCD.
    lcd.print("  S2: ");                         // Print text to the LCD.
    lcd.print(sensors.getTempCByIndex(1));       // Print sensor 1 value to the LCD.
    lcd.print("S3: ");                           // Print text to the LCD.
    lcd.print(sensors.getTempCByIndex(2));       // Print sensor 2 value to the LCD.
    lcd.print("  S4: ");                         // Print text to the LCD.
    lcd.print(sensors.getTempCByIndex(3));       // Print sensor 3 value to the LCD.
    lcd.print("S5: ");                           // Print text to the LCD.
    lcd.print(sensors.getTempCByIndex(4));       // Print sensor 4 value to the LCD.
 
  delay(6000);   // wait 1min

  lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
}






 

 
