
/*
 * Temperature logger with 
 * temp sensor DS18B20
 * SD card module from lctech (www.lctech-inc.com)
 */


#include <OneWire.h>               // temp sensor DS18B20 library
#include <DallasTemperature.h>     // temp sensor DS18B20 library

#include <SPI.h>                   // SD card module library
#include <SD.h>                    // SD card module library    

File dataLog;
boolean sd_ok = 0;

// DS18B20 temp sensor data wire is conntec to the Arduino digital pin 3
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);



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
}

  


void loop() 
{
    // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
    sensors.requestTemperatures(); 
  
    // print data on PC serial monitor
    Serial.println(sensors.getTempCByIndex(0)); 
    
    // write data to SD card
    if(sd_ok)
    {  // if the SD card was successfully initialized
      // open Log.txt file with write permission
      dataLog = SD.open("Log.txt", FILE_WRITE);
      dataLog.println( sensors.getTempCByIndex(0) );
      dataLog.close();   // close the file
    }
 
  
 
  delay(60000);   // wait 1min
}






 

 
