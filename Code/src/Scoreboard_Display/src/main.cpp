#include <RGBmatrixPanel.h>
#include <../utils/Pins.h>
#include <../lib/BaseballNR/BaseballNR.h>
#include <../lib/Cornhole/Cornhole.h>
#include <../lib/CursorSet/CursorSet.h>
#include <../utils/enumerations.h>

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

struct bballScore_t
{
  uint8_t redCol;
  uint8_t scoreRow;
  uint8_t distanceBetween;
  uint8_t tensOffset;
  uint8_t scoreSize;
  uint8_t brightness;
};

// Can't make both on the same line for Arduino reasons
struct choleScore_t
{
  uint8_t redCol;
  uint8_t scoreRow;
  uint8_t distanceBetween;
  uint8_t tensOffset;
  uint8_t scoreSize;
  uint8_t brightness;
};

FrameType currentFrame;

int cursorLocation = 0;

// Scoreboards
bballScore_t bballScore = {20, 1, 19, 6, 1, 3};
BaseballNR bballNR = BaseballNR(&matrix, bballScore.redCol, bballScore.scoreRow, bballScore.distanceBetween,
                                bballScore.tensOffset, bballScore.scoreSize, bballScore.brightness);

choleScore_t choleScore = {13, 4, 30, 7, 2, 3};
Cornhole chole = Cornhole(&matrix, choleScore.redCol, choleScore.scoreRow, choleScore.distanceBetween,
                          choleScore.tensOffset, choleScore.scoreSize, choleScore.brightness);

/**
 * ###############MOVE CORNHOLE BAR OVER 1 WHEN YOU GET SD READER#################
 */

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

  currentFrame = CornholeMain; // Testing

  // bballNR.displayFrame();
  chole.displayFrame();

  // bballNRSet.cursorSetSelect();
  bballNRSet.addCursorLocation(13, 20, 6);
  bballNRSet.addCursorLocation(4, 30, 5);
  bballNRSet.addCursorLocation(14, 30, 5);

  Serial.begin(9600);
}

void loop()
{
  recvOneChar();

  if (receivedChar == 'q')
  {
    // bballNRSet.cursorPrev();
    chole.decreaseRoundScore(BLUETEAM);
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
      chole.confirmRoundScore();
      break;
    }
  }
  else if (receivedChar == 'e')
  {
    // bballNRSet.cursorNext();
    chole.increaseRoundScore(BLUETEAM);
  }
}
