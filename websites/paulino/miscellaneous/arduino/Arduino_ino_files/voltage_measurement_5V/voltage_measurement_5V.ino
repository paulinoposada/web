// https://www.instructables.com/Voltage-Measurement-Using-Arduino/

// Voltage measurement with A0 analog input
// Voltage from 0 to 5V
// Data visible on serial monitor and recorded on SD card

#include <SPI.h>                   // SD card module library
#include <SD.h>                    // SD card module library    


float voltage, value;


// SD card: File and variabel sd_ok declaration  

File dataLog;

boolean sd_ok = 0;


void setup(){
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
        dataLog.println("VOLTAGE");
        dataLog.close();   // close the file
      }
      else
        Serial.println("error creating file.");
    }
  }
 
  Serial.println("VOLTAGE");

}


  

void loop(){
  value = analogRead(A0);
  voltage = value * 5.0/1023;
  Serial.print("Voltage= ");
  Serial.println(voltage);

  
  
      // write data to SD card
    if(sd_ok)
    {  // if the SD card was successfully initialized
      // open Log.txt file with write permission
      dataLog = SD.open("Log.txt", FILE_WRITE);
      


      // insert data in data file
      dataLog.print( voltage );
      dataLog.println(";");
      
      dataLog.close();   // close the file
    }
 

  
  delay(100);
}
