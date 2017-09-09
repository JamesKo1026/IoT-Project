#include <dht.h>
#include <SoftwareSerial.h>
 #define dht_dpin 2
 
SoftwareSerial BTserial(10,11);

dht DHT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTserial.begin(9600);
  //pinMode(9,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
    DHT.read11(dht_dpin);

    
      Serial.print (DHT.humidity);
      Serial.println (DHT.temperature);
   
      BTserial.write("H = ");
      BTserial.print(DHT.humidity);
      BTserial.println("%");
      BTserial.write("T = ");
      BTserial.print(DHT.temperature);
      BTserial.println("C");
    /*
     
     
      if (BTserial.available())
    {  
        
        Serial.write(BTserial.read());
    }
 
    // Read from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
        
        BTserial.write(Serial.read());  
    }
    */
    delay(1000);
  
}
