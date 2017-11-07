#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.


void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  pinMode(6, OUTPUT);      // initialize digital pin 13 as an output.
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  delay(100);
  
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
  SendMessage();
}
     }


 if ((distance>30)&&(distance<240))
     {
      {
  digitalWrite(6, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(800);              // wait for a second
  digitalWrite(6, LOW);    // turn the LED off by making the voltage LOW
  delay(800);  
  SendMessage();
}
     }

if (mySerial.available()>0)
   Serial.write(mySerial.read());

}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }




