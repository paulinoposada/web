/*
 https://arduinointro.com/articles/projects/how-to-make-an-alternate-blink-and-running-lights-effect
  
  Alternate Blink
    1.  Turn on LED1, turn off LED2 for 
        1 second (at the same time)
    2.  Turn off LED1, turn on LED2 for 
        1 second (at the same time)
    3.  Measure volatge on both LEDs  
    4.  Repeat
*/

  int pinA=9;
  int pinB=8;

  float voltage, value;

  void setup() {
    pinMode(pinA,OUTPUT);
    pinMode(pinB,OUTPUT);

    Serial.begin(9600); // initialize serial monitor
  }

  void loop() {
    //turn on pinA and turn off pinB
    digitalWrite(pinA,HIGH);
    digitalWrite(pinB,LOW);

  //voltage measurement pin A
    value = analogRead(A0);
    voltage = value * 5.0/1023;
    Serial.print("Voltage = ");
    Serial.println(voltage);
    
    //wait 1 sec
    delay(5000);

    //turn off pinA and turn on pinB
    digitalWrite(pinA,LOW);
    digitalWrite(pinB,HIGH);



    //voltage measurement pin B
    value = analogRead(A0);
    voltage = value * 5.0/1023;
    Serial.print("Voltage = ");
    Serial.println(voltage);

    //wait 1 sec
    delay(5000);


  }
