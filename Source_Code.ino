#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10 
#define RST_PIN 9

Servo servo;
MFRC522 mfrc522(SS_PIN, RST_PIN); 

byte card_ID[4]; //card UID size 4byte
byte Name1[4]={0xD3,0xA4,0x61,0x1E};//first UID card
byte Name2[4]={0x90,0x3A,0x6E,0x21};//second UID card

int NumbCard[2];
int j=0;        

String Name;//user name
String Number;
int n ;

void setup() {
  Serial.begin(9600); 
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  servo.attach(3);
  servo.write(110);
  
  Serial.println("CLEARSHEET");                 // clears starting at row 1
  Serial.println("LABEL,Name,Roll Number,Date,Time,");// make four columns
  }
    
void loop() {
  //look for new card
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//got to start of loop if there is no card present
 }

 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
 }
 
 for (byte i = 0; i < mfrc522.uid.size; i++) {
     card_ID[i]=mfrc522.uid.uidByte[i];

      if(card_ID[i]==Name1[i]){
       Name="John";
       Number="21BRS1111";

       j=0;//first number in the NumbCard array : NumbCard[j]
       
      }
      else if(card_ID[i]==Name2[i]){
       Name="Mathew";//user name
       Number="21BPS1234";//user number
       j=1;//Second number in the NumbCard array : NumbCard[j]

      }      
      else{
          goto cont;
      }
}
      if(NumbCard[j] == 1){
          servo.write(0);
            delay(3000);
            servo.write(110);
      }
      else{
            servo.write(0);
            delay(3000);
            servo.write(110);
          
      NumbCard[j] = 1;//put 1 in the NumbCard array : NumbCard[j]={1,1} to let the arduino know if the card was detecting 
      n++;//(optional)
      Serial.print("DATA," + Name);//send the Name to excel
      Serial.print(",");
      Serial.print(Number); //send the Number to excel
      Serial.println(",DATE,TIME,");
      Serial.println("SAVEWORKBOOKAS,Names/WorkNames");
      }
cont:
delay(2000);

}
