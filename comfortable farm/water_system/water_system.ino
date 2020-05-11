const int altra_water_house_echo = 9;
const int altra_water_house_tring = 8; 
const int altra_water_hangar_echo = 11;
const int altra_water_hangar_tring = 10; 
const int altra_water_irrigation_echo = 12;
const int altra_water_irrigation_tring =13;
const int irrigation_signal = 5;
int Thouse=A0;
int Thangar=A1;
int Tirrigation=A2;
int database_house=3;
int database_hangar=2;
int database_irrigation=4;
long value_water_house = 0; 
int cm_water_house = 0;
long value_water_hangar = 0; 
int cm_water_hangar = 0;
long value_water_irrigation= 0; 
int cm_water_irrigation = 0;

void setup() {
Serial.begin(9600);
pinMode(irrigation_signal,OUTPUT);
pinMode(database_house,OUTPUT);
pinMode(database_hangar,OUTPUT);
pinMode(database_irrigation,OUTPUT);
pinMode(Thouse,OUTPUT);
pinMode(Thangar,OUTPUT);
pinMode(Tirrigation,OUTPUT);
pinMode(altra_water_house_tring,OUTPUT);
pinMode(altra_water_house_echo,INPUT);
pinMode(altra_water_hangar_tring,OUTPUT);
pinMode(altra_water_hangar_echo,INPUT);
pinMode(altra_water_irrigation_tring,OUTPUT);
pinMode(altra_water_irrigation_echo,INPUT);
}

void loop() {
  digitalWrite(altra_water_house_tring,LOW);
 delayMicroseconds(2);
  digitalWrite(altra_water_house_tring,HIGH);
 delayMicroseconds(10);
  digitalWrite(altra_water_house_tring,LOW);
   value_water_house = pulseIn(altra_water_house_echo, HIGH);
  cm_water_house = (value_water_house*0.034)/2;
   digitalWrite(altra_water_hangar_tring,LOW);
 delayMicroseconds(2);
  digitalWrite(altra_water_hangar_tring,HIGH);
 delayMicroseconds(10);
  digitalWrite(altra_water_hangar_tring,LOW);
  value_water_hangar = pulseIn(altra_water_hangar_echo, HIGH);
  cm_water_hangar = (value_water_hangar*0.034)/2;
   digitalWrite(altra_water_irrigation_tring,LOW);
 delayMicroseconds(2);
  digitalWrite(altra_water_irrigation_tring,HIGH);
 delayMicroseconds(10);
  digitalWrite(altra_water_irrigation_tring,LOW);
  value_water_irrigation = pulseIn(altra_water_irrigation_echo, HIGH);
  cm_water_irrigation= (value_water_irrigation*0.034)/2;
  Serial.print("water in house tank:");
  Serial.println(cm_water_house);
  Serial.print("water in hangar tank:");
  Serial.println(cm_water_hangar);
  Serial.print("water in irrigation tank:");
  Serial.println(cm_water_irrigation);
  delay(1000);
  Serial.println();
 analogWrite(Thouse,cm_water_house);
 analogWrite(Thouse,cm_water_hangar);
 analogWrite(Thouse,cm_water_irrigation);
  if(cm_water_house ==10)
  {
    digitalWrite(database_house,HIGH);
    delay(5000);
    digitalWrite(database_house,LOW);
    
    }
  if(cm_water_hangar ==10)
  {
   digitalWrite(database_hangar,HIGH);
    delay(5000);
    digitalWrite(database_hangar,LOW);
    
    }
   if(cm_water_irrigation ==10)
  {
    digitalWrite(database_irrigation,HIGH);
    delay(5000);
    digitalWrite(database_irrigation,LOW);
    digitalWrite(irrigation_signal,HIGH);
    delay(5000);
    digitalWrite(irrigation_signal,LOW);
    }
}
