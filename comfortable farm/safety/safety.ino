#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial SIM900(3, 4); // SoftwareSerial SIM900(Rx, Tx)
int counter_for_message=0;
constexpr uint8_t redLed_house = 12;
constexpr uint8_t buzzer_house = 10;
constexpr uint8_t redLed_hangar = 6;
constexpr uint8_t buzzer_hangar = 7;
constexpr uint8_t smoke_house = A5;
constexpr uint8_t smoke_hangar = A4;
constexpr uint8_t signal_to_all_system = 11;
constexpr uint8_t IR_pin;
constexpr uint8_t data_base_signal = 5;
// Your threshold value
int sensorThres = 290;
constexpr uint8_t data_base_pin = 9;
void setup() {
  pinMode(redLed_house, OUTPUT);
  pinMode(buzzer_house, OUTPUT);
  pinMode(smoke_house, INPUT);
  pinMode(redLed_hangar, OUTPUT);
  pinMode(buzzer_hangar, OUTPUT);
  pinMode(smoke_hangar, INPUT);
  pinMode(IR_pin,INPUT);
  pinMode(signal_to_all_system,OUTPUT);
  pinMode(data_base_pin,OUTPUT);
  pinMode(data_base_signal,OUTPUT);
  Serial.begin(9600);
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

void loop() {
  int smoke_house = analogRead(smoke_house);
int smoke_hangar = analogRead(smoke_hangar);
  Serial.print("sensor in side house: ");
  Serial.println(smoke_house);
  Serial.print("sensor in side hangar: ");
  Serial.println(smoke_hangar);
  // Checks in house if it has reached the threshold value
  if(smoke_house > sensorThres)
  {
    //bool IR_signal=digitalRead(IR_pin);
   // if (IR_signal==LOW){
    digitalWrite(redLed_house, HIGH);
    tone(buzzer_house, 100, 200);
    if(counter_for_message==0){
    send_message_owner("there is fire in your house");
       send_message_CD();
       counter_for_message++;
       digitalWrite(data_base_pin,HIGH);
       }
        digitalWrite(signal_to_all_system,HIGH);
        delay(500);
 //}
   if(smoke_hangar > sensorThres)
  {
   
    digitalWrite(redLed_hangar, HIGH);
    tone(buzzer_hangar, 100, 200);
    if(counter_for_message==0){
    send_message_owner("there is fire in your hangar");
       send_message_CD_hangar();
       counter_for_message++;
       digitalWrite(data_base_signal,HIGH);
        delay(500);
  }
  }
  }else
  {
   digitalWrite(signal_to_all_system,LOW); 
    digitalWrite(data_base_signal,LOW);
    digitalWrite(redLed_house,LOW);
    digitalWrite(buzzer_house,LOW);}
   delay(5000); // clear area from gas 
   }
  
void send_message_owner(String message)// send message for owner of apartment
{
  SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);
  SIM900.println("AT+CMGS=\"+96299360318\""); // Replace it with your mobile number
  delay(100);
  SIM900.println(message);   // The SMS text you want to send
  delay(100);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900.println();
  delay(1000);
}


void send_message_CD()// send massage for civil defense
{
  String message="";
  SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);
  SIM900.println("AT+CMGS=\"+96299360318\""); // Replace it with your mobile number
  delay(100);
  SIM900.println(message);   // The SMS text you want to send
  delay(100);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900.println();
  delay(1000);
}

void send_message_CD_hangar()// send massage for civil defense
{
  String message="there is fire in house. the location is :ahmad basha al-jazzar street build number 11 hangar(https://goo.gl/maps/8KTbohQ64W39KoSS6)";
  SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);
  SIM900.println("AT+CMGS=\"+96299360318\""); // Replace it with your mobile number
  delay(100);
  SIM900.println(message);   // The SMS text you want to send
  delay(100);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900.println();
  delay(1000);
}
