int sensorpin =2;
int buzzer=8;
int i;
void setup() {
  // put your setup code here, to run once:
  pinMode(sensorpin,INPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  i=digitalRead(sensorpin);
  Serial.println(i);
  if(i==1)
  {
    tone(buzzer,523,100);
    delay(1000);
    tone(buzzer,587,100);
    delay(1000);
    tone(buzzer,659,100);
    delay(1000);
    tone(buzzer,698,100);
    delay(1000);
    tone(buzzer,784,100);
    delay(1000);
    tone(buzzer,880,100);
    delay(1000);
  }
}
