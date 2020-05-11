#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <DS3231.h>

RTClib RTC;
DS3231 Clock;

int Year;
int Month;
int Day;
int Hour;
int Minute;
int Second;
int tempC;
int interval;
int Minute_last;
bool scur_system,sefaty_system,food_system,water_system,Thouse,Thangar,Tirrigation;
File myFile_scur;
File myFile_sefaty;
File myFile_water;
File myFile_food;
File myFile_Thouse;
File myFile_Thangar;
File myFile_Tirrigation;
const uint8_t scur_pin=3;
const uint8_t sefaty_pin=2;
const uint8_t food_pin=9;
const uint8_t water_pin=5;
const uint8_t Thouse_pin=6;
const uint8_t Thangar_pin=7;
const uint8_t Tirrigation_pin=8;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
      }
delay(100);
  Serial.println("initialization done.");

pinMode(scur_pin,INPUT);
pinMode(sefaty_pin,INPUT);
pinMode(water_pin,INPUT);
pinMode(food_pin,INPUT);
pinMode(Thouse_pin,INPUT);
pinMode(Thangar_pin,INPUT);
pinMode(Tirrigation_pin,INPUT);
  }

void loop() {
  scur_system=digitalRead(scur_pin);
  sefaty_system=digitalRead(sefaty_pin);
  water_system=digitalRead(water_pin);
  food_system=digitalRead(food_pin);
    Thouse=digitalRead(Thouse_pin);
     Thangar=digitalRead(Thangar_pin);
        Tirrigation=digitalRead(Tirrigation_pin);
  interval = 1; //interval to write data
  DateTime now = RTC.now();
  Year = now.year();
  Month = now.month();
  Day = now.day();
  Hour = now.hour();
  Minute = now.minute();
  Second = now.second();
  tempC = Clock.getTemperature();
  
  if ((Minute % interval == 0)&(Minute_last!=Minute))
  {
    Minute_last = Minute;
  }

if( scur_system==true){
  myFile_scur = SD.open("securtiy.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile_scur) {
    myFile_scur.print(Year);
    myFile_scur.print("/");
    myFile_scur.print(Month);
    myFile_scur.print("/");
    myFile_scur.print(Day);
    myFile_scur.print(" ");
    myFile_scur.print(Hour);
    myFile_scur.print(":");
    myFile_scur.print(Minute);
    Serial.print("Writing to securtiy.txt...");
    myFile_scur.println(" securtiy high ");
    // close the file:
    myFile_scur.close();
    Serial.println("done.");
  }
}
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening securtiy.txt");
  }
delay(1000);

if( sefaty_system==true)
{
  myFile_sefaty = SD.open("safety.txt", FILE_WRITE);
  if (myFile_sefaty) {
    myFile_sefaty.print(Year);
    myFile_sefaty.print("/");
    myFile_sefaty.print(Month);
    myFile_sefaty.print("/");
    myFile_sefaty.print(Day);
    myFile_sefaty.print(" ");
    myFile_sefaty.print(Hour);
    myFile_sefaty.print(":");
    myFile_sefaty.print(Minute);
    Serial.print("Writing to sefaty.txt...");
    myFile_sefaty.println(" safety high ");
    // close the file:
    myFile_sefaty.close();
    Serial.println("done.");
  }}
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening safety.txt");
  }
  delay(500);
  if( water_system==true)
{
  myFile_water = SD.open("water.txt", FILE_WRITE);
  if (myFile_water) {
    myFile_water.print(Year);
    myFile_water.print("/");
    myFile_water.print(Month);
    myFile_water.print("/");
    myFile_water.print(Day);
    myFile_water.print(" ");
    myFile_water.print(Hour);
    myFile_water.print(":");
    myFile_water.print(Minute);
    Serial.print("Writing to water.txt...");
    myFile_water.println("water in food system is empty ");
    // close the file:
    myFile_water.close();
    Serial.println("done.");
  }
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening water.txt");
  }

  if( food_system==HIGH)
{
  myFile_food = SD.open("food.txt", FILE_WRITE);
  if (myFile_food) {
    myFile_food.print(Year);
    myFile_food.print("/");
    myFile_food.print(Month);
    myFile_food.print("/");
    myFile_food.print(Day);
    myFile_food.print(" ");
  myFile_food.print(Hour);
    myFile_food.print(":");
    myFile_food.print(Minute);
    Serial.print("Writing to food.txt...");
    myFile_food.println("food is empty ");
    // close the file:
    myFile_food.close();
    Serial.println("done.");
  } 
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening food.txt");
  }
   if( Thouse==HIGH)
{
  myFile_Thouse = SD.open("Thouse.txt", FILE_WRITE);
  if (myFile_Thouse) {
    myFile_Thouse.print(Year);
    myFile_Thouse.print("/");
    myFile_Thouse.print(Month);
    myFile_Thouse.print("/");
    myFile_Thouse.print(Day);
    myFile_Thouse.print(" ");
  myFile_Thouse.print(Hour);
    myFile_Thouse.print(":");
    myFile_Thouse.print(Minute);
    Serial.print("Writing to Thouse.txt...");
    myFile_Thouse.println("house water tank is empty ");
    // close the file:
    myFile_Thouse.close();
    Serial.println("done.");
  } 
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening Thouse.txt");
  }
   if( Thangar==HIGH)
{
  myFile_Thangar = SD.open("Thangar.txt", FILE_WRITE);
  if (myFile_Thangar) {
    myFile_Thangar.print(Year);
    myFile_Thangar.print("/");
    myFile_Thangar.print(Month);
    myFile_Thangar.print("/");
    myFile_Thangar.print(Day);
    myFile_Thangar.print(" ");
  myFile_Thangar.print(Hour);
    myFile_Thangar.print(":");
    myFile_Thangar.print(Minute);
    Serial.print("Writing to Thangar.txt...");
    myFile_Thangar.println("hangar water tank is empty ");
    // close the file:
    myFile_Thangar.close();
    Serial.println("done.");
  } 
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening Thangar.txt");
  }
     if( Tirrigation==HIGH)
{
  myFile_Tirrigation = SD.open("Tirrigation.txt", FILE_WRITE);
  if (myFile_Tirrigation) {
    myFile_Tirrigation.print(Year);
    myFile_Tirrigation.print("/");
    myFile_Tirrigation.print(Month);
    myFile_Tirrigation.print("/");
    myFile_Tirrigation.print(Day);
    myFile_Tirrigation.print(" ");
  myFile_Tirrigation.print(Hour);
    myFile_Tirrigation.print(":");
    myFile_Tirrigation.print(Minute);
    Serial.print("Writing to Thangar.txt...");
    myFile_Tirrigation.println("irrigation water tank is empty ");
    // close the file:
    myFile_Tirrigation.close();
    Serial.println("done.");
  } 
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening Tirrigation.txt");
  }
}
