#include <SoftwareSerial.h>

//Pins
#define RxD 2
#define TxD 3
#define led 0
#define button 1

SoftwareSerial BT(RxD, TxD);

void setup() {
  pinMode(led,OUTPUT);
  pinMode(button,OUTPUT);

  BT.begin(9600);
}

void loop(){ 
  if(digitalRead(button) == HIGH)
  {
    digitalWrite(led, HIGH);
    BT.write('Y');
    delay(250);
  }
  else
  {
    digitalWrite(led, LOW);
    BT.write('N');
    delay(250);
  }

  
}
