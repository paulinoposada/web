 
/*
 * Temperature logger with 
 * multiple temperature sensors DS18B20
 * SD card module from lctech (www.lctech-inc.com) -works only with original Arduino not with clone
 * Temp ssensors on pin 9
 * Sd card data (CS ) on pin 10
 */


#include <OneWire.h>               // DS18B20 temp sensor library
#include <DallasTemperature.h>     // DS18B20 temp sensor library

#include <SPI.h>                   // SD card module library
#include <SD.h>                    // SD card module library    

#include <LiquidCrystal.h>        // LCD module library code

File dataLog;
boolean sd_ok = 0;
int loopcount = 0;
int sensor = 0;               // identifies each sensor 
int dl = 2000;                // delay time 2000 = 2 s
int time_count = 0;           // time passed since sketch start

// DS18B20 temp sensor data wire is conntec to the Arduino digital pin 9
#define ONE_WIRE_BUS 9

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

// LCD - initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


int numberOfDevices; // Number of temperature devices found

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address



void setup() {
  
  // open serial communications
  Serial.begin(9600);

//********************temp sensor setup start***************
    // Start up the library
  sensors.begin();
  
  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++) {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i)) {
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
       }// else
   }// for
//********************temp sensor setup end***************




//********************SD card setup start***************
  // initialize the SD card
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) 
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
        // write text to 'Log.txt' file
        dataLog.println("TEMPERATURE");
        dataLog.println();      
        dataLog.close();   // close the file
        
      }
      else
        Serial.println("error creating file.");
    }
  }
  
  
  Serial.println("TEMPERATURE");
//********************SD card setup end***************  


//******************** LCD setup start***************  
lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
//******************** LCD setup end***************

        
} //(finish setup)

  


void loop() 
{
    // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
    sensors.requestTemperatures(); 


  
    // print data on PC serial monitor**************************

  // Loop through each device, print data on PC serial monitor
  for(int i=0;i<numberOfDevices; i++) {
    Serial.print(sensors.getTempCByIndex(i));
    Serial.print(";");
     }
    
    Serial.print("time = ");
    Serial.print(time_count);    
    Serial.print(" s");
    Serial.println();
            


    
    // write data to SD card**************************
    if(sd_ok)
    {  // if the SD card was successfully initialized
      // open Log.txt file with write permission
      dataLog = SD.open("Log.txt", FILE_WRITE);

      for(int i=0;i<numberOfDevices; i++) {
      dataLog.print(sensors.getTempCByIndex(i));
      dataLog.print(";");
      
        }
      dataLog.print("time = ");
      dataLog.print(time_count);
      dataLog.print(" s");
      dataLog.println();      
      
      dataLog.close();   // close the file
    }


  // write data to LCD **************************
 for(int i=0;i<numberOfDevices; i++) {
    lcd.clear();                                       //Clears the LCD screen and positions the cursor in the upper-left corner.
    lcd.print("sen ");                                 // Print a message to the LCD.
    lcd.print(sensor);
    lcd.print(" = ");
    lcd.print(sensors.getTempCByIndex(sensor));        // Print temp sensor 0 to the LCD
    lcd.print(" C");
    sensor = sensor + 1;
    delay(dl);                                       // wait 2 sec showing sensor value on LCD
     }

      
  time_count = loopcount * numberOfDevices * (dl / 1000) ;
  loopcount = loopcount + 1;
   
  sensor = 0;
  
}


// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}


 

 
