#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Serial.begin(9600);
  
}
void loop() {
  // put your main code here, to run repeatedly:
  String i;
  lcd.setCursor(0,0);
  i=Serial.readString();
  if(i!=NULL)
  {
    lcd.clear();
    lcd.print(i);
  }
}
