#include <IRremote.h>
#include <Servo.h>
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
Servo sg90;
bool incounter=false;
bool outcounter=false;
bool TVcounter=false;
bool windowcounter=false;
bool conditioncounter=false;
bool heatercounter=false;
constexpr uint8_t in_side_light=2;
constexpr uint8_t out_side_light=3;
constexpr uint8_t TV=4;
constexpr uint8_t window=5;
constexpr uint8_t servoPin = 8;
constexpr uint8_t scurPin = 9;
constexpr uint8_t safety_system_pin=11;
constexpr uint8_t safety_pin=12;
constexpr uint8_t condition_pin=0;
constexpr uint8_t condition_read = 6;
constexpr uint8_t heater_pin=1;
constexpr uint8_t heater_read=13;
constexpr uint8_t opendoor=7;
void setup(){
  Serial.begin(9600);
  pinMode(in_side_light,OUTPUT);
  pinMode(out_side_light,OUTPUT);
  pinMode(TV,OUTPUT);
   pinMode(window,OUTPUT);
    pinMode(scurPin,OUTPUT);
    pinMode(condition_pin,OUTPUT);
    pinMode(heater_pin,OUTPUT);
    pinMode(condition_read,INPUT);
    pinMode(heater_read,INPUT);
  pinMode(safety_system_pin,INPUT);
  pinMode(safety_pin,OUTPUT);
  pinMode(opendoor,OUTPUT);
  irrecv.enableIRIn();
  irrecv.blink13(true);
 sg90.attach(servoPin);  //Declare pin 8 for servo
  sg90.write(0); // Set initial position at 0 degrees
  }
void loop(){
  digitalWrite(scurPin,LOW); 
  if(digitalRead(safety_system_pin)==LOW )
  {
    irrecv.decode(&results);
    //if (irrecv.decode(&results)){
      Serial.println(results.value);
  
  switch(results.value){
          case 0xFF6897: //IR button "0"
          light();
          break;
          case 0xFF30CF: //IR button "1"
          insidelight();
          break;
          case 0xFF18E7: //IR button "2"
          outsidelight();
          break;
          case 0xFF7A85: //IR button "3"
          Serial.println("the door is opened");
          digitalWrite(scurPin,HIGH); 
          delay(1000);         
          break;
          case 0xFF10EF: //IR button "4"
          Tv();
          break;
          case 0xFF38C7: //IR button "5"
          Window();
          break;
          case 0xFF5AA5: //IR button "6"
          condition();
          break;
          case 0xFF42BD: //IR button "7"
          heater();// momken n3mlh ll3r9' aldata 3la lcd ale kberh
          break;
          case 0xFF4AB5: //IR button "8"
          digitalWrite(opendoor,HIGH);//momken n3melh 3shan n6'am al rie
          break;
          case 0xFF52AD: //IR button "9"
          Serial.println("sending HIGH signal for safety system");
          digitalWrite(safety_pin,HIGH);
          windowcounter=false;
          Window();
          delay(1000);
          digitalWrite(safety_pin,LOW);
          break;          
          }
          irrecv.resume();
  }
  else
  {
    outcounter=true;
    incounter=true;
    heatercounter=false;
    windowcounter=false;
    light();
     Window();
     heater();
     }

  if(digitalRead(condition_read)==HIGH)
  {
    conditioncounter=false;
    condition();
    }
else if(digitalRead(heater_read)==HIGH)
{
  heatercounter=false;
  heater();
  }
}
  void insidelight()
  {
    if (incounter==true){
    digitalWrite(in_side_light,LOW);
  Serial.println("in side light is off");
  incounter=false;
  }
    else{
    digitalWrite(in_side_light,HIGH);
    Serial.println("in side light is on");
    incounter=true;
    }    
    }
     void outsidelight()
  {
    if (outcounter==true){
    digitalWrite(out_side_light,LOW);
  Serial.println("out side light is off");
  outcounter=false;
  }
    else{
    digitalWrite(out_side_light,HIGH);
    Serial.println("out side light is on");
    outcounter=true;
    }    
    }
    void light()
  {
    if (outcounter==true||incounter==true){
    digitalWrite(out_side_light,LOW);
    digitalWrite(in_side_light,LOW);
  Serial.println("all light is off");
  outcounter=false;
  incounter=false;
  }
    else{
    digitalWrite(out_side_light,HIGH);
    digitalWrite(in_side_light,HIGH);
    Serial.println("all light is on");
    outcounter=true;
    incounter=true;
    }    
    }
    void Tv()
  {
    if (TVcounter==true){
    digitalWrite(TV,LOW);
  Serial.println("TV is off");
  TVcounter=false;
  }
    else{
    digitalWrite(TV,HIGH);
    Serial.println("TV is on");
    TVcounter=true;
    }    
    }
    void Window ()
    {
        if (windowcounter==true){
    sg90.write(0);
  Serial.println("window is closed");
  windowcounter=false;
  }
    else{
     sg90.write(90);
    Serial.println("window is opened");
    windowcounter=true;
    } 
      }
      
      void condition()
    {
        if (conditioncounter==true){
          digitalWrite(condition_pin,LOW);
  Serial.println("condition is closed");
 conditioncounter=false;
  }
    else{
      digitalWrite(condition_pin,HIGH);
    Serial.println("condition is opened");
    conditioncounter=true;
    } 
      }
        void heater()
    {
        if (heatercounter==true){
          digitalWrite(heater_pin,LOW);
  Serial.println("heater is closed");
heatercounter=false;
  }
    else{
      digitalWrite(heater_pin,HIGH);
    Serial.println("heater is opened");
    heatercounter=true;
    } 
      }
