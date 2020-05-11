#include <DS3231.h>
#include <Servo.h>
#include <SoftwareSerial.h>
RTClib RTC;
DS3231 Clock;
SoftwareSerial SIM900(3, 4); // SoftwareSerial SIM900(Rx, Tx)
int Year;
int Month;
int Date;
int Hour;
int Minute;
int Second;
int tempC;
int interval;
int Minute_last;
const int altra_food_echo = 4;
const int altra_food_tring = 5;
const int altra_water_echo = 6;
const int altra_water_tring = 7;
long value_food = 0;
long value_water = 0;
int cm_food = 0;
int cm_water = 0;
int ledPin=4;
Servo myservo1; 
Servo myservo2; 
void setup()
{
Serial.begin(9600);
pinMode(altra_water_echo,INPUT);
pinMode(altra_food_echo,INPUT);
pinMode(altra_water_tring,OUTPUT);
pinMode(altra_food_tring,OUTPUT);
pinMode(ledPin, OUTPUT);
myservo1.attach(9);
myservo2.attach(10);
 // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);

  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  // Set module to send SMS data to serial out upon receipt
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}
void loop()
{
digitalWrite(altra_food_tring,LOW);
 delayMicroseconds(2);
  digitalWrite(altra_food_tring,HIGH);
 delayMicroseconds(10);
  digitalWrite(altra_food_tring,LOW);
value_food = pulseIn(altra_food_echo, HIGH) ;
cm_food = value_food / 58;

digitalWrite(altra_water_tring,LOW);
 delayMicroseconds(2);
  digitalWrite(altra_water_tring,HIGH);
 delayMicroseconds(10);
  digitalWrite(altra_water_tring,LOW);
value_water = pulseIn(altra_water_echo, HIGH) ;
cm_water = value_water / 58;
Serial.print(cm_food);
delay(500);
DateTime now = RTC.now();
if(cm_food<9)
{
  if(now.hour() == 8 && now.minute() == 59&& now.second()==59)
  {
     myservo1.write(90);
     delay(2000);
     myservo1.write(0);
   }
  
  }
  else
  {
    Serial.print("The food box is empty");
    send_message_owner("The food box is empty");
    }
  if(cm_water<9)
{
  if(now.hour() == 8 && now.minute() == 59&& now.second()==59)
  {
     myservo2.write(90);
     delay(2000);
     myservo2.write(0);
   }
  else
  {
    Serial.print("The water box is empty");
    send_message_owner("The water box is empty");
    }
  }
}



void send_message_owner(String message)// send message for owner of apartment
{
  SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);
  SIM900.println("AT+CMGS=\"+962799360318\""); // Replace it with your mobile number
  delay(100);
  SIM900.println(message);   // The SMS text you want to send
  delay(100);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900.println();
  delay(1000);
}
