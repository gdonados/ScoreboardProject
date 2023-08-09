#include "Cornhole.h"

Cornhole::Cornhole(RGBmatrixPanel *matrix, int redScoreCol, int scoreRow, int distance, int leftScoreTensOffset, int size, int brightnessScalar)
    : CustomFrame(matrix, redScoreCol, scoreRow, distance, leftScoreTensOffset, size, brightnessScalar)
{
  redRoundScore = 0;
  blueRoundScore = 0;
}

void Cornhole::displayFrame()
{
  CustomFrame::displayFrame(CornholeFile);
  drawSmallNumber(redRoundScore, RED_FIRSTNUM_COL, SMALL_NUM_ROW, red);
  drawSmallNumber(blueRoundScore, BLUE_FIRSTNUM_COL, SMALL_NUM_ROW, blue);

  initScoreMain();
}

void Cornhole::drawSmallNumber(int value, int col, int row, uint16_t color)
{
  // If there is an invalid value, print square
  if (value < MIN_ROUND_SCORE || value > MAX_ROUND_SCORE)
  {
    for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 5; j++)
      {
        matrix->drawPixel(col + i, row + j, color);
      }
    }
  }

  else
  {
    if (value > 9)
    {
      for (int i = 0; i < 5; i++)
      {
        for (int j = 0; j < 5; j++)
        {
          if (smallNumbers[1][j][i] == 1)
            matrix->drawPixel(col + i - SMALL_NUM_OFFSET, row + j, color);
        }
      }
    }

    for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 5; j++)
      {
        if (smallNumbers[value % 10][j][i] == 1)
          matrix->drawPixel(col + i, row + j, color);
      }
    }
  }
}

void Cornhole::increaseRoundScore(Team team)
{
  uint16_t color = team == REDTEAM ? red : blue;
  uint8_t &score = team == REDTEAM ? redRoundScore : blueRoundScore;
  byte col = team == REDTEAM ? RED_FIRSTNUM_COL : BLUE_FIRSTNUM_COL;

  if (score < 12)
  {
    drawSmallNumber(score, col, SMALL_NUM_ROW, off);
    score++;
    drawSmallNumber(score, col, SMALL_NUM_ROW, color);
  }
}

void Cornhole::decreaseRoundScore(Team team)
{
  uint16_t color = team == REDTEAM ? red : blue;
  uint8_t &score = team == REDTEAM ? redRoundScore : blueRoundScore;
  byte col = team == REDTEAM ? RED_FIRSTNUM_COL : BLUE_FIRSTNUM_COL;

  if (score > 0)
  {
    drawSmallNumber(score, col, SMALL_NUM_ROW, off);
    score--;
    drawSmallNumber(score, col, SMALL_NUM_ROW, color);
  }
}

void Cornhole::bust(Team team)
{
}

void Cornhole::confirmRoundScore()
{
  oldRedScore = redScore;
  oldBlueScore = blueScore;

  redScore += redRoundScore;
  blueScore += blueRoundScore;

  drawSmallNumber(redRoundScore, RED_FIRSTNUM_COL, SMALL_NUM_ROW, off);
  drawSmallNumber(blueRoundScore, BLUE_FIRSTNUM_COL, SMALL_NUM_ROW, off);

  redRoundScore = 0;
  blueRoundScore = 0;

  drawSmallNumber(redRoundScore, RED_FIRSTNUM_COL, SMALL_NUM_ROW, red);
  drawSmallNumber(blueRoundScore, BLUE_FIRSTNUM_COL, SMALL_NUM_ROW, blue);

  updateMainScore();
}

// Different due to collision with progress bar
void Cornhole::updateMainScore()
{
  // Red
  oldRedScore >= 10 ? matrix->setCursor(redScoreCol - leftScoreTensOffset, scoreRow) : matrix->setCursor(redScoreCol, scoreRow);
  matrix->setTextColor(off);
  matrix->print(String(oldRedScore));
  redScore >= 10 ? matrix->setCursor(redScoreCol - leftScoreTensOffset, scoreRow) : matrix->setCursor(redScoreCol, scoreRow);
  matrix->setTextColor(red);
  matrix->print(String(redScore));

  // Blue
  oldBlueScore >= 10 ? matrix->setCursor(blueScoreCol - leftScoreTensOffset, scoreRow) : matrix->setCursor(blueScoreCol, scoreRow);
  matrix->setTextColor(off);
  matrix->print(String(oldBlueScore));
  blueScore >= 10 ? matrix->setCursor(blueScoreCol - leftScoreTensOffset, scoreRow) : matrix->setCursor(blueScoreCol, scoreRow);
  matrix->setTextColor(blue);
  matrix->print(String(blueScore));

  if (redScore > MAX_ROUND_SCORE)
    bust(REDTEAM);

  if (blueScore > MAX_ROUND_SCORE)
    bust(BLUETEAM);
}

void Cornhole::updateProgressBar(Team team)
{
}

void Cornhole::toggleBust()
{
  doBust = !doBust;
}
