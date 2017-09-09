#include <dht.h>
#include <LiquidCrystal_I2C.h>
#define dht_dpin 2

LiquidCrystal_I2C lcd(0x27 ,2 ,1 ,0 ,4 ,5 ,6 ,7 ,3 ,POSITIVE);

dht DHT;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  
}

void loop() {
  // put your main code here, to run repeatedly:
    DHT.read11(dht_dpin);
    lcd.setCursor(0,0);
    lcd.print("H = ");
    lcd.print(DHT.humidity);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("T = ");
    lcd.print(DHT.temperature);
    lcd.print("C");
  delay(1000);
  
}
