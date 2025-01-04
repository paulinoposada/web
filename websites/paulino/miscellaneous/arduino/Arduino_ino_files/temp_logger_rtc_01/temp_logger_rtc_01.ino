 
/*
 * Temperature logger with 
 * 5 temperature sensors DS18B20
 * SD card module from lctech (www.lctech-inc.com)
 * rtc module DS1307
 */


#include <OneWire.h>               // temp sensor DS18B20 library
#include <DallasTemperature.h>     // temp sensor DS18B20 library

#include <SPI.h>                   // SD card module library
#include <SD.h>                    // SD card module library    

#include <RTClib.h>                // RCT module library


File dataLog;
boolean sd_ok = 0;

// DS18B20 temp sensor data wire is conntec to the Arduino digital pin 2
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);



RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};






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
        // write some texts to 'Log.txt' file
        dataLog.println("TEMPERATURE");
        dataLog.close();   // close the file
      }
      else
        Serial.println("error creating file.");
    }
  }
 
  Serial.println("TEMPERATURE");



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
}


  


void loop() 
{
  
    // Sets DateTime using the RTC
    DateTime now = rtc.now();
      
  
    // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
    sensors.requestTemperatures(); 


    // print date & time on PC serial monitor
    Serial.print("Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
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
      dataLog.print("Date & Time: ");
      dataLog.print(now.year(), DEC);
      dataLog.print('/');
      dataLog.print(now.month(), DEC);
      dataLog.print('/');
      dataLog.print(now.day(), DEC);
      dataLog.print(" (");
      dataLog.print(daysOfTheWeek[now.dayOfTheWeek()]);
      dataLog.print(") ");
      dataLog.print(now.hour(), DEC);
      dataLog.print(':');
      dataLog.print(now.minute(), DEC);
      dataLog.print(':');
      dataLog.println(now.second(), DEC);


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
 
  
 
  delay(3000);   // wait 1min
}






 

 
