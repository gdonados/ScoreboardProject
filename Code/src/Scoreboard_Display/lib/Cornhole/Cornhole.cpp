#include "Cornhole.h"

Cornhole::Cornhole(RGBmatrixPanel *matrix, int redScoreCol, int scoreRow, int distance, int leftScoreTensOffset, int size, int brightnessScalar)
    : BaseFrame(matrix, redScoreCol, scoreRow, distance, leftScoreTensOffset, size, brightnessScalar)
{
  redRoundScore = 0;
  blueRoundScore = 0;
  winningScore = 21; // Change for init screen
  barStep = (float)BAR_HEIGHT / (float)winningScore;
  redComboScore = 0;
  blueComboScore = 0;
}

void Cornhole::displayFrame()
{
  BaseFrame::displayFrame(CornholeFile);
  drawSmallNumber(redRoundScore, RED_FIRSTNUM_COL, SMALL_NUM_ROW, red);
  drawSmallNumber(blueRoundScore, BLUE_FIRSTNUM_COL, SMALL_NUM_ROW, blue);

  initScoreMain();
  updateProgressBar();
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

  updateProgressBar();
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

  updateProgressBar();
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
  updateProgressBar();
}

// Different due to collision with progress bar
void Cornhole::updateMainScore()
{
  // Red
  matrix->setTextSize(2);
  oldRedScore >= 10 ? matrix->setCursor(redScoreCol - leftScoreTensOffset, scoreRow) : matrix->setCursor(redScoreCol, scoreRow);
  matrix->setTextColor(off);
  matrix->print(String(oldRedScore));

  if (redScore > winningScore && doBust)
    bust(REDTEAM);

  redScore >= 10 ? matrix->setCursor(redScoreCol - leftScoreTensOffset, scoreRow) : matrix->setCursor(redScoreCol, scoreRow);
  matrix->setTextColor(red);
  matrix->print(String(redScore));

  // Blue
  oldBlueScore >= 10 ? matrix->setCursor(blueScoreCol - leftScoreTensOffset, scoreRow) : matrix->setCursor(blueScoreCol, scoreRow);
  matrix->setTextColor(off);
  matrix->print(String(oldBlueScore));

  if (blueScore > winningScore && doBust)
    bust(BLUETEAM);

  blueScore >= 10 ? matrix->setCursor(blueScoreCol - leftScoreTensOffset, scoreRow) : matrix->setCursor(blueScoreCol, scoreRow);
  matrix->setTextColor(blue);
  matrix->print(String(blueScore));

  if (redScore == winningScore || blueScore > winningScore)
  {
    (redScore > winningScore) ? winScreen(REDTEAM) : winScreen(BLUETEAM);
  }
}

void Cornhole::bust(Team team)
{
  uint8_t textCol = (team == REDTEAM) ? redScoreCol - leftScoreTensOffset : blueScoreCol - leftScoreTensOffset;
  uint8_t textRow = BUST_ROW;
  uint8_t &score = (team == REDTEAM) ? redScore : blueScore;

  score = BUST_RESET_VALUE;

  matrix->setTextSize(1);

  for (int i = 0; i < 3; i++)
  {
    matrix->setCursor(textCol, textRow);
    matrix->setTextColor(yellow);
    matrix->print("BUST");
    delay(300);

    matrix->setCursor(textCol, textRow);
    matrix->setTextColor(off);
    matrix->print("BUST");
    delay(300);
  }

  updateMainScore();
}

void Cornhole::updateProgressBar()
{
  redComboScore = (float)(redScore + redRoundScore) * barStep;
  uint8_t redBar = (int)redComboScore;
  redBar = (redBar >= BAR_HEIGHT) ? BAR_HEIGHT - 1 : redBar;
  int redBarColor = (redScore + redRoundScore > winningScore && doBust) ? yellow : red;

  blueComboScore = (float)(blueScore + blueRoundScore) * barStep;
  uint8_t blueBar = (int)blueComboScore;
  blueBar = (blueBar >= BAR_HEIGHT) ? BAR_HEIGHT - 1 : blueBar;
  int blueBarColor = (blueScore + blueRoundScore > winningScore && doBust) ? yellow : blue;

  // Erase old
  matrix->drawLine(RED_BAR_BASE_COL, BAR_BASE_ROW, RED_BAR_BASE_COL, BAR_BASE_ROW - BAR_HEIGHT + 1, off);
  matrix->drawLine(RED_BAR_BASE_COL + 1, BAR_BASE_ROW, RED_BAR_BASE_COL + 1, BAR_BASE_ROW - BAR_HEIGHT + 1, off);
  matrix->drawLine(BLUE_BAR_BASE_COL, BAR_BASE_ROW, BLUE_BAR_BASE_COL, BAR_BASE_ROW - BAR_HEIGHT + 1, off);
  matrix->drawLine(BLUE_BAR_BASE_COL + 1, BAR_BASE_ROW, BLUE_BAR_BASE_COL + 1, BAR_BASE_ROW - BAR_HEIGHT + 1, off);

  // Draw new
  matrix->drawLine(RED_BAR_BASE_COL, BAR_BASE_ROW, RED_BAR_BASE_COL, BAR_BASE_ROW - redBar, redBarColor);
  matrix->drawLine(RED_BAR_BASE_COL + 1, BAR_BASE_ROW, RED_BAR_BASE_COL + 1, BAR_BASE_ROW - redBar, redBarColor);
  matrix->drawLine(BLUE_BAR_BASE_COL, BAR_BASE_ROW, BLUE_BAR_BASE_COL, BAR_BASE_ROW - blueBar, blueBarColor);
  matrix->drawLine(BLUE_BAR_BASE_COL + 1, BAR_BASE_ROW, BLUE_BAR_BASE_COL + 1, BAR_BASE_ROW - blueBar, blueBarColor);
}

void Cornhole::toggleBust()
{
  doBust = !doBust;
}
