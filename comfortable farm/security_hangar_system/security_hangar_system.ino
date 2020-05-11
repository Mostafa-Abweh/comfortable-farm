const int buttonPin = 8; 
const int ledPin_green =3; 
const int ledPin_red =  4;
const int ledPin_alaret = 7;
const int altra_horse_echo = 52;
const int altra_horse_tring = 53;
 const int vcc = 22;
const int altra_theaf_echo = 4;
const int altra_theaf_tring = 5; 
const int buzzer= 6; 
int buttonState = 0;
int buttonState2 = 0;
int buttonState3 = 0;  
long value_horse = 0; 
long value_theaf = 0; 
int cm_horse = 0;
int cm_theaf = 0;
int max=50;
bool state=false;
void setup() {
  Serial.begin(9600);
  pinMode(vcc, OUTPUT);
  digitalWrite(vcc,HIGH);
  pinMode(ledPin_green, OUTPUT);
  pinMode(ledPin_red, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(ledPin_alaret, OUTPUT);
  pinMode(altra_horse_tring,OUTPUT);
pinMode(altra_horse_echo,INPUT);
pinMode(altra_theaf_tring,OUTPUT);
pinMode(altra_theaf_echo,INPUT);
}

void loop() {
  digitalWrite(altra_horse_tring,LOW);
 delayMicroseconds(2);
  digitalWrite(altra_horse_tring,HIGH);
 delayMicroseconds(10);
  digitalWrite(altra_horse_tring,LOW);
   value_horse = pulseIn(altra_horse_echo, HIGH);
  cm_horse = (value_horse*0.034)/2;
  
  digitalWrite(altra_theaf_tring,LOW);
 delayMicroseconds(2);
  digitalWrite(altra_theaf_tring,HIGH);
 delayMicroseconds(10);
  digitalWrite(altra_theaf_tring,LOW);
   value_theaf = pulseIn(altra_theaf_echo, HIGH);
  cm_theaf = (value_theaf*0.034)/2;
  Serial.println(cm_horse );
  Serial.println();
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if(buttonState == HIGH)
  {
    mood();
   
  }
   if(state==true){
    digitalWrite(ledPin_green, HIGH);
    digitalWrite(ledPin_red, LOW);
  }
  else
  {
    digitalWrite(ledPin_green, LOW);
    digitalWrite(ledPin_red, HIGH);
    if(cm_horse>=10)
    {
      digitalWrite(ledPin_alaret, HIGH);
      tone(buzzer,100);
    }
    if((max-cm_theaf)<=10)
    {
    Serial.println("there someone open the hanger door .");
     digitalWrite(ledPin_alaret, HIGH);
      tone(buzzer,100);
    }
    else
    {
    Serial.println("there is a theaf .");
       digitalWrite(ledPin_alaret, HIGH);
      tone(buzzer,100);
      }
  }
       digitalWrite(ledPin_alaret, LOW);
       noTone(buzzer);
     }
  
  


void mood()
{
  if(state == true)
  state=false;
  else 
  state=true;
  }
