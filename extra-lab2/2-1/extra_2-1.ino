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
  int i;
  lcd.print(" FUCK ");
  for(i=0;i<11;i++)
  {
    lcd.setCursor(i,0);
    
    lcd.print("HELLO");
    delay(500);
    lcd.clear();
    
  }
  for(i=11;i>0;i--)
  {
    lcd.setCursor(i,0);
    
    lcd.print("HELLO");
    delay(500);
    lcd.clear();
  }
}
