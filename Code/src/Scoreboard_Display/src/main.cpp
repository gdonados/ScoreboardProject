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
  BaseballNRMain // Baseball "No-Run"
};

FrameType currentFrame;

int cursorLocation = 0;

// Scoreboards
BaseballNR bballNR = BaseballNR(&matrix, 3);
// Cornhole  chole     = Cornhole();

CursorSet bballNRSet = CursorSet(&matrix, 3, 20, 6, 2);

// Temp serial vars
char receivedChar = ' ';

void recvOneChar()
{
  if (Serial.available() > 0)
  {
    receivedChar = Serial.read();
  }
}

void setup()
{
  // put your setup code here, to run once:
  matrix.begin();

  currentFrame = BaseballNRMain; // Testing

  bballNR.displayFrame();
  // chole.displayFrame(matrix);

  bballNRSet.cursorSetSelect();
  bballNRSet.addCursorLocation(13, 20, 6);
  bballNRSet.addCursorLocation(4, 30, 5);
  bballNRSet.addCursorLocation(14, 30, 5);
  Serial.println("656 Colors: ");
  Serial.println(matrix.Color333(7, 7, 7));
}

void loop()
{
  recvOneChar();

  if (receivedChar == 'q')
  {
    bballNRSet.cursorPrev();
  }
  else if (receivedChar == 'w')
  {
    switch (currentFrame)
    {
    case BaseballNRMain:
      cursorLocation = bballNRSet.getCursorIndex();

      if (cursorLocation == 0)
      {
        bballNR.hitSingle();
      }
      else if (cursorLocation == 1)
      {
        bballNR.hitDouble();
      }
      else if (cursorLocation == 2)
      {
        bballNR.recordStrike();
      }
      else
      {
        bballNR.recordBall();
      }

      break;

    case CornholeMain:
      // chole.increaseRoundScore(matrix, true);
      break;
    }
  }
  else if (receivedChar == 'e')
  {
    bballNRSet.cursorNext();
  }
}
