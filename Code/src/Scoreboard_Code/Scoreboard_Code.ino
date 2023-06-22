#include "Pins.h"
//#include "CustomFrame.h"
#include <RGBmatrixPanel.h>
#include "BaseballNR.h"

RGBmatrixPanel matrix = RGBmatrixPanel(A, B, C, D, CLK, LAT, OE, false, 64);

BaseballNR bballNR = BaseballNR();
//CustomFrame cFrame = CustomFrame();

//Temp serial vars
char receivedChar = ' ';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start...");
  matrix.begin();

  bballNR.genBaseballNR(matrix);
}

void loop() {
  recvOneChar();

  if(receivedChar == '1')
  {
    bballNR.hitSingle(matrix);
  }
  else if(receivedChar == '2')
  {
    bballNR.hitDouble(matrix);
  }
  else if(receivedChar == 'z')
  {
    bballNR.recordBall(matrix);
  }
  else if(receivedChar == 'x')
  {
    bballNR.recordStrike(matrix);
  }
}

void recvOneChar() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
    }
}
