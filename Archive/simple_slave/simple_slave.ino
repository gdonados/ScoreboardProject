#define Rx 2
#define Tx 3
#define led 4

#include <SoftwareSerial.h> 
SoftwareSerial BT(2, 3); // RX | TX 

void setup() {
  // put your setup code here, to run once:
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  char c = ' ';
  if(BT.available())
  {
    c = BT.read();
  }

  if(c == 'Y')
  {
    digitalWrite(led, HIGH);
    Serial.print("Received Y");
  }

  if(c == 'N')
  {
    digitalWrite(led, LOW);
    Serial.print("Received N");
  }

  c = ' ';
}
