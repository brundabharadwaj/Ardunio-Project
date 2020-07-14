#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
char msg;
char call;
const int sumplevel = 5; //Switch Connected to PIN 5
const int min_level = 6; //Switch Connected to PIN 6
const int top_level = 7; //Switch Connected to PIN 7
const int MotorPin = 8; //Motor Connected to PIN 8
const int GSMmodule=9;//to get message
int top_level_status = 0; //Variable for reading switch status
int sump_level_status = 0; //Variable for reading switch status
int min_level_status = 0;
void setup() {
 pinMode(MotorPin, OUTPUT); //Motor PIN is Output    
    pinMode(sumplevel, INPUT_PULLUP); //Switch PIN is Input
    pinMode(min_level, INPUT_PULLUP); //Switch PIN is Input
    pinMode(top_level, INPUT_PULLUP); //Switch PIN is Input
     mySerial.begin(9600);   // Setting the baud rate of GSM Module  
    Serial.begin(9600);  
}

void loop() {

sump_level_status = digitalRead(sumplevel); 
min_level_status = digitalRead(min_level);
top_level_status = digitalRead(top_level);
if (sump_level_status == HIGH) //If the switch is pressed
    {
       digitalWrite(MotorPin, LOW); //Motor ON
       if (Serial.available()>0)
       {
         SendMessage();
       }
       
       delay(1000); //1 Second Delay
       } 
        else if ((top_level_status == HIGH) && (min_level_status==HIGH))//If the switch is pressed
    {
        digitalWrite(MotorPin, HIGH); //Motor OFF
        delay(1000); //1 Second Delay
        }
       else if ((top_level_status == LOW) && (min_level_status==HIGH))//If the switch is pressed
    {
        digitalWrite(MotorPin, HIGH); //Motor OFF
        delay(1000); //1 Second Delay
        }
        else if ((top_level_status == LOW) && (min_level_status==LOW))//If the switch is pressed
    {
        digitalWrite(MotorPin, LOW); //Motor ON
         if (Serial.available()>0)
       {
         SendMessage();
       }
        
        delay(1000); //1 Second Delay
        }
  
}
void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919731787159\"\r"); 
  delay(1000);
  mySerial.println("Motor ON ");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
