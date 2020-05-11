#include <DS3231.h>
RTClib RTC;
DS3231 Clock;
const int rain_pin = 1 ;
const int water_pin = 2 ;
const int led_pin = 3 ;
int Year;
int Month;
int Date;
int Hour;
int Minute;
int Second;
int tempC;
void setup() {
Serial.begin(9600);
pinMode(rain_pin,INPUT);
pinMode(water_pin,INPUT);
pinMode(led_pin,OUTPUT);
}

void loop() {
  bool rain_value= digitalRead(rain_pin);
  bool water_value= digitalRead(water_pin);
  DateTime now = RTC.now();
  if(rain_value==LOW || water_value == LOW)
  {
  if((now.hour() == 6) ||  (now.hour() == 12))
  {
    digitalWrite(led_pin,HIGH);
    delay(2000);
    digitalWrite(led_pin,LOW);
  }
  }
  else
  delay(86400000);//one day
  }
