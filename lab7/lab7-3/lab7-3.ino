#include <dht.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2 ,1 ,0 ,4 ,5 ,6 ,7 ,3 ,POSITIVE);
 #define dht_dpin 2
 
SoftwareSerial BTserial(10,11);

dht DHT;

void setup() {
  // put your setup code here, to run once:
  
  BTserial.begin(9600);
  //pinMode(9,OUTPUT);
  lcd.begin(16,2);
  
}

void loop() {
  // put your main code here, to run repeatedly:
     DHT.read11(dht_dpin);
     
     lcd.setCursor(0,0);
     switch(BTserial.read()){
     
     case '0':
        BTserial.write("T = ");
         BTserial.print(DHT.temperature);
        lcd.print("T = ");
        lcd.print(DHT.temperature);
          break;
     case '1':
        BTserial.write("H = ");
        BTserial.print(DHT.humidity);
        lcd.print("H = ");
        lcd.print(DHT.humidity);
          break;
     default :
          break;
     }
    delay(1000);
  
}
