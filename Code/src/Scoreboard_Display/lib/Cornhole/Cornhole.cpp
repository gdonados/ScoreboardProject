#include "Cornhole.h"

Cornhole::Cornhole()
{
  redScore = 0;
  blueScore = 0;
  redScoreCol = 000; //CHANGE
  blueScoreCol = 000;
  scoreRow = 000;
  leftScoreTensOffset = 000;
}

void Cornhole::displayFrame(RGBmatrixPanel matrix)
{
  CustomFrame::displayFrame(matrix, CornholeFile);
  drawSmallNumber(matrix, redScore, RED_FIRSTNUM_COL, SMALL_NUM_ROW, matrix.Color333(7, 0, 0));
  drawSmallNumber(matrix, blueScore, BLUE_FIRSTNUM_COL, SMALL_NUM_ROW, matrix.Color333(0, 4, 7));
}

void Cornhole::drawSmallNumber(RGBmatrixPanel matrix, int value, int col, int row, uint16_t color)
{
  //If there is an invalid value, print square
  if(value < 0 || value > 12)
  {
    for(int i = 0; i < 5; i++)
    {
      for(int j = 0; j < 5; j++)
      {
        matrix.drawPixel(col+i, row+j, color);
      }
    }
  }

  else
  {
    if(value > 9)
    {
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; j < 5; j++)
        {
          if(smallNumbers[1][j][i] == 1)
            matrix.drawPixel(col+i-SMALL_NUM_OFFSET, row+j, color);
        }
      }
    }

    for(int i = 0; i < 5; i++)
    {
      for(int j = 0; j < 5; j++)
      {
        if(smallNumbers[value%10][j][i] == 1)
          matrix.drawPixel(col+i, row+j, color);
      }
    }
  }
}

void Cornhole::increaseRoundScore(RGBmatrixPanel matrix, boolean redTeam)
{
  uint16_t colorOff = matrix.Color333(0, 0, 0);
  uint16_t color;
  redTeam ? color = matrix.Color333(7, 0, 0) : color = matrix.Color333(0, 4, 7);

  if(redTeam && redScore < 12)
  {
    drawSmallNumber(matrix, redScore, RED_FIRSTNUM_COL, SMALL_NUM_ROW, colorOff);
    redScore++;
    drawSmallNumber(matrix, redScore, RED_FIRSTNUM_COL, SMALL_NUM_ROW, color);
  }
  else if(!redTeam && blueScore < 12)
  {
    drawSmallNumber(matrix, blueScore, BLUE_FIRSTNUM_COL, SMALL_NUM_ROW, colorOff);
    blueScore++;
    drawSmallNumber(matrix, blueScore, BLUE_FIRSTNUM_COL, SMALL_NUM_ROW, color);
  }
}

void Cornhole::decreaseRoundScore(RGBmatrixPanel matrix, boolean redTeam)
{
  uint16_t colorOff = matrix.Color333(0, 0, 0);
  uint16_t color;
  redTeam ? color = matrix.Color333(7, 0, 0) : color = matrix.Color333(0, 4, 7);

  if(redTeam && redScore >= 0)
  {
    drawSmallNumber(matrix, redScore, RED_FIRSTNUM_COL, SMALL_NUM_ROW, colorOff);
    redScore--;
    drawSmallNumber(matrix, redScore, RED_FIRSTNUM_COL, SMALL_NUM_ROW, color);
  }
  else if(!redTeam && blueScore >= 0)
  {
    drawSmallNumber(matrix, blueScore, BLUE_FIRSTNUM_COL, SMALL_NUM_ROW, colorOff);
    blueScore--;
    drawSmallNumber(matrix, blueScore, BLUE_FIRSTNUM_COL, SMALL_NUM_ROW, color);
  }
}
