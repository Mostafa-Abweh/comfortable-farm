#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
RTClib RTC;
DS3231 Clock;
LiquidCrystal_I2C lcd(0x27, 16, 4);


void setup() {
  // put your setup code here, to run once:
 lcd.begin();   // LCD screen
  lcd.backlight();
  lcd.clear();
  }

void loop() {
  // put your main code here, to run repeatedly:

int TI= analogRead(A0);
int Thangar= analogRead(A1);
int Thouse= analogRead(A2);
int H;
int M;
int S;
 DateTime now = RTC.now();
H = now.hour();
  M= now.minute();
S = now.second();
  lcd.clear();
        lcd.setCursor(0, 0);
            if(Thouse>0)
        {
        lcd.print(" THouse ="+String(Thouse)+ "CM");
        }
        else
        {
          lcd.print(" THouse =***empty***");
          }
        lcd.setCursor(0, 1);
          if(Thangar>0)
        {
        lcd.print(" THangar="+String(Thangar)+"CM");
        }
        else
        {
          lcd.print(" THangar=***empty***");
          }
        lcd.setCursor(0,2);
        if(TI>0)
        {
        lcd.print(" TIrrigation="+String(TI)+"CM");
        }
        else
        {
          lcd.print(" TIrrigation=***empty***");
          }
        lcd.setCursor(0, 3);
         lcd.print(" Time now:"+String(H)+ ":"+String(M) +":"+String(S) );
       
}
