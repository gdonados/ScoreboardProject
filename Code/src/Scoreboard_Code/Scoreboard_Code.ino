#include "Pins.h"
#include "CustomFrame.h"
#include <RGBmatrixPanel.h>

RGBmatrixPanel matrix = RGBmatrixPanel(A, B, C, D, CLK, LAT, OE, false, 64);

CustomFrame cFrame = CustomFrame();

//Temp serial vars
char receivedChar = ' ';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start...");
  matrix.begin();

  cFrame.genBaseballNR(matrix);
}

void loop() {
  recvOneChar();

  if(receivedChar == 'r')
  {
    cFrame.increaseScore(matrix, false);
  }
  else if(receivedChar == 'b')
  {
    cFrame.increaseScore(matrix, true);
  }
  else if(receivedChar == '1')
  {
    cFrame.hitSingle(matrix);
  }
  else if(receivedChar == '2')
  {
    cFrame.hitDouble(matrix);
  }
  else if(receivedChar == '3')
  {
    cFrame.walk(matrix);
  }
}

void recvOneChar() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
    }
}
