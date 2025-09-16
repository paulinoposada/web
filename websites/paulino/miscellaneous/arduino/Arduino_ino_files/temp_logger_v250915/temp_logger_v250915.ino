 
/*
 * Temperature logger with 
 * multiple temperature sensors DS18B20
 * SD card module from lctech (www.lctech-inc.com)
 */


#include <OneWire.h>               // temp sensor DS18B20 library
#include <DallasTemperature.h>     // temp sensor DS18B20 library

#include <SPI.h>                   // SD card module library
#include <SD.h>                    // SD card module library    

File dataLog;
boolean sd_ok = 0;
int loopcount = 0;

// DS18B20 temp sensor data wire is conntec to the Arduino digital pin 3
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address



void setup() {
  
  // open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

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
    }

//********************temp sensor setup end***************




//********************SD card setup start***************
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

        Serial.print("Found device ");
        Serial.print(i, DEC);
        Serial.print(" with address: ");
        printAddress(tempDeviceAddress);
        Serial.println();
      
          

        dataLog.println();      
        dataLog.close();   // close the file
        
      }
      else
        Serial.println("error creating file.");
    }
  }
 
//********************SD card setup end***************  



    Serial.println("TEMPERATURE");
  }

}

  


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
    Serial.print("loopcount =");
    Serial.print(loopcount);
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
      dataLog.print("loopcount =");
      dataLog.print(loopcount);
      dataLog.println();      
      
      dataLog.close();   // close the file
    }
 
  
 
  delay(3000);   // wait 1min
  loopcount = loopcount + 1;
}


// function to print a device address
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}


 

 
