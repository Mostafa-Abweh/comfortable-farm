int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor  
int Irrigation_system=5;
int IR_system=4; 
void setup() 
{
  Serial.begin(9600);   
pinMode(Irrigation_system, OUTPUT);
  pinMode(IR_system, OUTPUT);
}

void loop() 
{
Serial.print("Soil Moisture = ");    
val = analogRead(soilPin);
Serial.println(val);
if (val!=1023){
  digitalWrite(Irrigation_system,HIGH);
  digitalWrite(IR_system,HIGH);
  }

delay(2000);//take a reading every 2 second
}
