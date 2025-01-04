// https://www.instructables.com/Voltage-Measurement-Using-Arduino/

// Voltage measurement with A0 analog input
// Voltage from 0 to 5V
// Data visible on serial monitor and recorded on SD card

#include <SPI.h>                   // SD card module library
#include <SD.h>                    // SD card module library    


float voltage_1, value_1, voltage_2, value_2;


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
  
  // write voltatge_1 to Seriel monitor
  value_1 = analogRead(A0);
  voltage_1 = value_1 * 5.0/1023;
  Serial.print("Voltage_1= ");
  Serial.print(voltage_1);
  Serial.print("; ");
  
  // write voltatge_2 to Seriel monitor
value_2 = analogRead(A1);
  voltage_2 = value_2 * 5.0/1023;
  Serial.print("Voltage_2= ");
  Serial.println(voltage_2);
  
  
      // write data to SD card
    if(sd_ok)
    {  // if the SD card was successfully initialized
      // open Log.txt file with write permission
      dataLog = SD.open("Log.txt", FILE_WRITE);
      


      // insert data in data file
      dataLog.print( voltage_1 );
      dataLog.print(";" );
      dataLog.print( voltage_2 );
      dataLog.println(";");
      
      dataLog.close();   // close the file
    }
 

  
  delay(100);
}
