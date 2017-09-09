
#include <IRremote.h>
#include <NewTone.h>
////////////////////////////////////////////////////////////////////////
// Arduino Bluetooth Interface with Brainsense
// 
// This is example code provided by Pantech Prolabs. and is provided
// license free.
////////////////////////////////////////////////////////////////////////

int RECV_PIN = 2;
int buzzer=8;  
IRrecv irrecv(RECV_PIN); 
decode_results results; 

#define LED 13
#define BAUDRATE 57600
#define DEBUGOUTPUT 0

int buzzer=8;
int j_x=5;
int j_y=6;
int j_z=7;
#define powercontrol 10

// checksum variables
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;

// system variables
long lastReceivedPacket = 0;
boolean bigPacket = false;

//////////////////////////
// Microprocessor Setup //
//////////////////////////
void setup() 

{
  /*
  pinMode(j_x,INPUT);
  pinMode(j_y,INPUT); 
  pinMode(j_z,INPUT);
  */
  Serial.begin(BAUDRATE); 
  irrecv.enableIRIn();// USB
}

////////////////////////////////
// Read data from Serial UART //
////////////////////////////////
byte ReadOneByte() 

{
  int ByteRead;
  while(!Serial.available());
  ByteRead = Serial.read();

#if DEBUGOUTPUT  
  Serial.print((char)ByteRead);   // echo the same byte out the USB serial (for debug purposes)
#endif

  return ByteRead;
}

/////////////
//MAIN LOOP//
/////////////
void loop() 

{
  // Look for sync bytes
  if(ReadOneByte() == 170) 
  {
    if(ReadOneByte() == 170) 
    {
        payloadLength = ReadOneByte();
      
        if(payloadLength > 169)                      //Payload length can not be greater than 169
        return;
        generatedChecksum = 0;        
        for(int i = 0; i < payloadLength; i++) 
        {  
        payloadData[i] = ReadOneByte();            //Read payload into memory
        generatedChecksum += payloadData[i];
        }   

        checksum = ReadOneByte();                      //Read checksum byte from stream      
        generatedChecksum = 255 - generatedChecksum;   //Take one's compliment of generated checksum

        if(checksum == generatedChecksum) 
        {    
          poorQuality = 200;
          attention = 0;
          meditation = 0;

          for(int i = 0; i < payloadLength; i++) 
          {                                          // Parse the payload
          switch (payloadData[i]) 
          {
          case 2:
            i++;            
            poorQuality = payloadData[i];
            bigPacket = true;            
            break;
          case 4:
            i++;
            attention = payloadData[i];                        
            break;
          case 5:
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
            i = i + 3;
            break;
          case 0x83:
            i = i + 25;      
            break;
          default:
            break;
          } // switch
        } // for loop

#if !DEBUGOUTPUT

        // *** Add your code here ***

        if(bigPacket) 
        {
        
          if(poorQuality == 0)
             digitalWrite(LED, HIGH);
          else
            digitalWrite(LED, LOW);
          
          //Serial.print("PoorQuality: ");
          //Serial.print(poorQuality, DEC);
          Serial.print(" Attention: ");
          Serial.print(attention, DEC);
          //Serial.print(" Time since last packet: ");
          //Serial.print(millis() - lastReceivedPacket, DEC);
          //lastReceivedPacket = millis();
          //Serial.print("\n");

          if(attention>30)
          {
            int to[]={523,587,659,698,784,880,988,1047};
            int m[10000];
            int i;
            int top=0;
            if (irrecv.decode(&results)) {
              {
                if(results.value==0xC101E57B){
                  NewTone(buzzer,523,100);
                  m[top++]=523;
                }
                if(results.value==0x9716BE3F){
                  NewTone(buzzer,587,100);
                  m[top++]=587;
                }
                if(results.value==0x3D9AE3F7){
                  NewTone(buzzer,659,100);
                  m[top++]=659;
                }
                if(results.value==0x6182021B){
                  NewTone(buzzer,698,100);
                  m[top++]=698;
                }
                if(results.value==0x8C22657B){
                  NewTone(buzzer,784,100);
                  m[top++]=784;
                }
                if(results.value==0x488F3CBB){
                  NewTone(buzzer,880,100);
                  m[top++]=880;
                }
                if(results.value==0x0449E79F){
                  NewTone(buzzer,988,100);
                  m[top++]=988;
                }
                if(results.value==0x32C6FDF7){
                  NewTone(buzzer,1047,100);
                  m[top++]=1047;
                }
                if(results.value==0x1BC0157B){
                  for(i=0;i<8;i++){
                     NewTone(buzzer,to[i],100);
                     delay(100);
                  }
                }
                if(results.value==0x3EC3FC1B){
                  for(i=7;i>=0;i--){
                     NewTone(buzzer,to[i],100);
                     delay(100);
                  }
                }
                if(results.value==0xE318261B){
                  for(i=0;i<=top;i++){
                     NewTone(buzzer,m[i],100);
                     delay(100);
                  }
                }
              } 
              Serial.print("results value is "); 
              Serial.println(results.value,HEX);
              /*Serial.print(", bits is ");
              Serial.print(results.bits);
              Serial.print(", decode_type is ");
              Serial.println(results.decode_type);*/
              irrecv.resume(); 
            }              
          }
        }
#endif        
        bigPacket = false;        
      }
      else {
        // Checksum Error
      }  // end if else for checksum
    } // end if read 0xAA byte
  } // end if read 0xAA byte
}
