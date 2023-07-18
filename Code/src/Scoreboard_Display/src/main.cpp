#include <Pins.h>
#include <RGBmatrixPanel.h>
#include <BaseballNR.h>
#include <Cornhole.h>
#include <CursorSet.h>

RGBmatrixPanel matrix = RGBmatrixPanel(A, B, C, D, CLK, LAT, OE, false, 64);

enum FrameType
{
  MainMenu,
  Generic,
  CornholeOptions,
  CornholeMain,
  BaseballNROptions,
  BaseballNRMain //Baseball "No-Run"
};

FrameType currentFrame;

int cursorLocation = 0;

//Scoreboards
BaseballNR  bballNR   = BaseballNR();
Cornhole    chole     = Cornhole();

CursorSet bballNRSet  = CursorSet(3, 20, 6);

//Temp serial vars
char receivedChar = ' ';

void recvOneChar()
{
  if (Serial.available() > 0)
  {
    receivedChar = Serial.read();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start...");
  matrix.begin();

  currentFrame = CornholeMain; //Testing

  // bballNR.displayFrame(matrix);
  chole.displayFrame(matrix);

  //bballNRSet.cursorSetSelect(matrix);
  bballNRSet.addCursorLocation(13, 20, 6);
  bballNRSet.addCursorLocation(4, 30, 5);
  bballNRSet.addCursorLocation(14, 30, 5);
}

void loop() {
  recvOneChar();

  if(receivedChar == 'q')
  {
    //bballNRSet.cursorPrev(matrix);
  }
  else if(receivedChar == 'w')
  {
    switch(currentFrame)
    {
      case BaseballNRMain:
        cursorLocation = bballNRSet.getCursorIndex();

        if(cursorLocation == 0)
        {
          bballNR.hitSingle(matrix);
        }
        else if(cursorLocation == 1)
        {
          bballNR.hitDouble(matrix);
        }
        else if(cursorLocation == 2)
        {
          bballNR.recordStrike(matrix);
        }
        else
        {
          bballNR.recordBall(matrix);
        }
        
        break;

      case CornholeMain:
        chole.increaseRoundScore(matrix, true);
        break;
    }
  }
  else if(receivedChar == 'e')
  {
    bballNRSet.cursorNext(matrix);
  }
}
