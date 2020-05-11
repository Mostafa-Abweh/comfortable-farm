// Include required libraries
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <SPI.h>

// Create instances
SoftwareSerial SIM900(3, 4); // SoftwareSerial SIM900(Rx, Tx)
SoftwareSerial mySerial(1, 0); //A6 Tx & Rx is connected to Arduino #1 & #0
MFRC522 mfrc522(9, 8); // MFRC522 mfrc522(SS_PIN, RST_PIN)
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo sg90;
// Initialize Pins for led's, servo and buzzer
// Blue LED is connected to 5V
constexpr uint8_t greenLed = 7;
constexpr uint8_t redLed = 6;
constexpr uint8_t servoPin = 13;
constexpr uint8_t buzzerPin = 5;
constexpr uint8_t safetysystemPin = 17;
constexpr uint8_t opensignal = 15;
constexpr uint8_t closesignal = 14;
constexpr uint8_t ultraPin = 22;
int messagecunter=0; 
constexpr uint8_t data_base_pin=48;
constexpr uint8_t IRpin = 16;
char initial_password[4] = {'1', '2', '3', '4'};  // Variable to store initial password
String tagUID = "74 92 47 83";
String tagcd = "62 6F 2B 79";// String to store UID of tag. 
char password[4];   // Variable to store users password
boolean RFIDMode = true; // boolean to change modes
boolean NormalMode = true;
boolean safety_signal = LOW;
boolean IR_signal = LOW;
// boolean to change modes
char key_pressed = 0; // Variable to store incoming keys
uint8_t i = 0;  // Variable used for counter

// defining how many rows and columns our keypad have
const byte rows = 4;
const byte columns = 4;

// Keypad pin map
char hexaKeys[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Initializing pins for keypad
byte row_pins[rows] = {A0, A1, A2, A3};
byte column_pins[columns] = {4, 3, 2};

// Create instance for keypad
Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

void setup() {
  // Arduino Pin configuration
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
   pinMode(data_base_pin, OUTPUT);
  pinMode( safetysystemPin ,INPUT);
   pinMode(ultraPin, INPUT);
   pinMode(IRpin,INPUT);
  sg90.attach(servoPin);  //Declare pin 8 for servo
  sg90.write(0); // Set initial position at 0 degrees

  lcd.begin();   // LCD screen
  lcd.backlight();
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC5
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


  lcd.clear(); // Clear LCD screen
}

void loop() {
safety_signal=digitalRead(safetysystemPin);
IR_signal=digitalRead(IRpin);
  
  if (safety_signal== LOW) 
  {
  if(IR_signal== LOW) 
  {  
 
  if (NormalMode == false) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
      lcd.print("  Closed");


    // Function to receive message
    receive_message();
        long duration, distance;
     duration = pulseIn(ultraPin, HIGH);
  distance = (duration/2) / 29.1;
  if ( distance>20)
  {
    digitalWrite(buzzerPin, HIGH);
        digitalWrite(redLed, HIGH);
        if(messagecunter==0){
        send_message("Someone break the house");
    send_message_Police();
    messagecunter++;
    digitalWrite(data_base_pin,HIGH);
    }
    
    }
    else
    { digitalWrite(buzzerPin, LOW);
        digitalWrite(redLed, LOW);
        digitalWrite(data_base_pin,LOW);
        delay(20000);
       messagecunter=0;
        }
    
  }

  else if ( NormalMode==false) {
     // Function to receive message
    receive_message();


 
    // System will first look for mode
    if (RFIDMode == true) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Door Lock");
      lcd.setCursor(0, 1);
      lcd.print(" Scan Your Tag ");

      // Look for new cards
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
      }

      // Select one of the cards
      if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
      }

      //Reading from the card
      String tag = "";
      for (byte j = 0; j < mfrc522.uid.size; j++)
      {
        tag.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " "));
        tag.concat(String(mfrc522.uid.uidByte[j], HEX));
      }
      tag.toUpperCase();

      //Checking the card
      if (tag.substring(1) == tagUID)
      {
        // If UID of tag is matched.
        lcd.clear();
        lcd.print("Tag Matched");
        digitalWrite(greenLed, HIGH);
        delay(1500);
        digitalWrite(greenLed, LOW);

        lcd.clear();
        lcd.print("Enter Password:");
        lcd.setCursor(0, 1);
        RFIDMode = false; // Make RFID mode false
      }else if (tag.substring(1)==tagcd)
      {
        sg90.write(90);
        lcd.clear();
        lcd.print("Tag Matched");
        digitalWrite(greenLed, HIGH);
        delay(1500);
        digitalWrite(greenLed, LOW);
       lcd.clear();
       lcd.print("Emergency");
       delay(5000);
       sg90.write(0);

        }

      else
      {
        // If UID of tag is not matched.
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wrong Tag Shown");
        lcd.setCursor(0, 1);
        lcd.print("Access Denied");
        digitalWrite(buzzerPin, HIGH);
        digitalWrite(redLed, HIGH);
        send_message("Someone Tried with wrong tag \nType 'close' to halt the system.");
        delay(1500);
        digitalWrite(buzzerPin, LOW);
        digitalWrite(redLed, LOW);
        lcd.clear();
      }
    }

    // If RFID mode is false, it will look for keys from keypad
    if (RFIDMode == false) {
      key_pressed = keypad_key.getKey(); // Storing keys
      if (key_pressed)
      {
        password[i++] = key_pressed; // Storing in password variable
        lcd.print("*");
      }
      if (i == 4) // If 4 keys are completed
      {
        delay(200);
        if (!(strncmp(password, initial_password, 4))) // If password is matched
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Pass Accepted");
          lcd.setCursor(0, 1);
          lcd.print("Door opend");
          sg90.write(90); // Door Opened
          digitalWrite(greenLed, HIGH);
          send_message("Door Opened \nIf it wasn't you, type 'close' to halt the system.");
          delay(1500);
          digitalWrite(greenLed, LOW);
          sg90.write(0); // Door Closed
          lcd.clear();
          i = 0;
          RFIDMode = true; // Make RFID mode true
        }
        else    // If password is not matched
        {
          lcd.clear();
          lcd.print("Wrong Password");
          digitalWrite(buzzerPin, HIGH);
          digitalWrite(redLed, HIGH);
          send_message("Someone Tried with wrong Password \nType 'close' to halt the system.");
          delay(1000);
          digitalWrite(buzzerPin, LOW);
          digitalWrite(redLed, LOW);
          lcd.clear();
          i = 0;
          RFIDMode = true;  // Make RFID mode true
        }
      }
    }
  }
}
else //for IR signal
{
  lcd.clear();
lcd.print("door opened");
sg90.write(90);
digitalWrite(greenLed,HIGH);
delay(5000);              
sg90.write(0);
digitalWrite(greenLed,LOW);
}}
else //for safety signal
{
  sg90.write(90);
  lcd.clear();
  lcd.setCursor(0, 0);
lcd.print("There is a fire");
lcd.setCursor(0, 1);
lcd.print("or gas infiltration");
digitalWrite(redLed,HIGH);
digitalWrite(buzzerPin,HIGH);
delay(5000);
sg90.write(0);
digitalWrite(buzzerPin,LOW);
digitalWrite(redLed,LOW);
}
}

// Receiving the message
void receive_message()
{
  char incoming_char = 0; //Variable to save incoming SMS characters
  String incomingData;   // for storing incoming serial data
  
  if (SIM900.available() > 0)
  {
    incomingData = SIM900.readString(); // Get the incoming data.
    delay(10);
  }
  // if received command is to open the door
  if (incomingData.indexOf("open") >= 0)
  {
    sg90.write(90);
    NormalMode = true;
    send_message("Opened");
    delay(10000);
    sg90.write(0);
  }
  // if received command is to halt the system
  if (incomingData.indexOf("close") >= 0)
  {
     lcd.clear();
    lcd.print("closed");
    NormalMode = false;
    send_message("Closed");
  }
  incomingData = "";
}

// Function to send the message
void send_message(String message)
{ 
  SIM900.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);
  SIM900.println("AT+CMGS=\"+962787647961\""); // Replace it with your mobile number
  delay(100);
  SIM900.println(message);   // The SMS text you want to send
  delay(100);
  SIM900.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900.println();
  delay(1000);
}
void send_message_Police()
{
  // Replace the value of message by locatin of the house 
  String message="there is someone break my house. the location is :ahmad basha al-jazzar street build number 11 round 3(https://goo.gl/maps/8KTbohQ64W39KoSS6)";
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
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
