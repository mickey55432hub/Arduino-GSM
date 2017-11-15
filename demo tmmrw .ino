#include <SoftwareSerial.h>
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 4
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 5
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);
#define TRIGGER_PIN  7  
// Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8 
 
 void message();
 void message1();
 
 
void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  pinMode(6, OUTPUT);    
  Serial.begin(9600);
  while(!Serial);
  //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(9600);
  delay(1000);
  Serial.println("Setup Complete!");
   pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  delay(100);
  message();
}
 
 
 
 
void loop()
{
    float duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2); 
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
    Serial.print(" Ping: ");
    Serial.print(distance); // Convert ping time to distance in cm and print result (0 = outside set distance range)
    Serial.println("cm");

 if ((distance>0)&&(distance<20))
     {
      {
  digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);              // wait for a second
  digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
  delay(100);  
  message();
}
     }
     
//Read SIM800 output (if available) and print it in Arduino IDE Serial Monitor
  if(serialSIM800.available()){
    Serial.write(serialSIM800.read());
  }
  //Read Arduino IDE Serial Monitor inputs (if available) and send them to SIM800
  if(Serial.available()){    
    serialSIM800.write(Serial.read());
  }
}





void message()
{
  Serial.println("Sending SMS test...");
  //Set SMS format to ASCII
  serialSIM800.write("AT+CMGF=1\r\n");
  delay(1000);
 
  //Send new SMS command and message number
  serialSIM800.write("AT+CMGS=\"0973XXXXXXXXX\"\r\n");
  delay(1000);
   
  //Send SMS content
  serialSIM800.write("TEST");
  delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
  serialSIM800.write((char)26);
  delay(1000);
     
  Serial.println("SMS Sent! Test Successfull");
}





void message1()
{
  Serial.println("Sending SMS for water level...");
  //Set SMS format to ASCII
  serialSIM800.write("AT+CMGF=1\r\n");
  delay(1000);
 
  //Send new SMS command and message number
  serialSIM800.write("AT+CMGS=\"0973XXXXXXXXX\"\r\n");
  delay(1000);
   
  //Send SMS content
  serialSIM800.write("Water level is  high, Please switch off the motor");
  delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
  serialSIM800.write((char)26);
  delay(1000);
     
  Serial.println("SMS Sent!");
}



