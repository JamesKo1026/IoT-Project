int photocellpin =2;
int photocellval =0;

int ledpin= 9;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  photocellval =analogRead(photocellpin);
  Serial.println(photocellval);
  if(photocellval<=600)
  {
    digitalWrite(ledpin,HIGH);
  }
  else
  {
    digitalWrite(ledpin,LOW);
  }
  delay(100);
}
