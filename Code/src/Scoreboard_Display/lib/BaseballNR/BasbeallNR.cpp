#include "BaseballNR.h"

BaseballNR::BaseballNR(RGBmatrixPanel *matrix, int redScoreCol, int scoreRow, int distance, int leftScoreTensOffset, int size, int brightnessScalar)
    : CustomFrame(matrix, redScoreCol, scoreRow, distance, leftScoreTensOffset, size, brightnessScalar)
{
  inning = 1;
  top = true;
}

// Bundeled commands for generated baseball no run scorebug
void BaseballNR::displayFrame()
{
  CustomFrame::displayFrame(BaseballNRFile);

  // defaults
  baseEncoding = 0;
  totalBalls = 4;
  totalStrikes = 3;
  totalOuts = 3;

  balls = 0;
  strikes = 0;
  outs = 0;

  initScoreMain();

  drawBSONodes(totalBalls, BALL_START_ROW);
  drawBSONodes(totalStrikes, STRIKE_START_ROW);
  drawBSONodes(totalOuts, OUT_START_ROW);

  // Innings
  drawInning();
}

// Increases red or blue score
// Currently need switch for frame selecting, due to scores being in different spots
void BaseballNR::increaseBBallScore()
{
  uint16_t color;
  top ? color = red : color = blue;

  CustomFrame::increaseScore(top ? REDTEAM : BLUETEAM);
}

void BaseballNR::drawBaseSprite(int startCol, int startRow, boolean turnOn)
{
  int endCol = startCol + BASE_SIZE;
  int endRow = startRow + BASE_SIZE;

  if (turnOn)
  {
    // Fill out base
    matrix->drawLine(startCol, startRow, endCol, endRow, yellow);
    for (int i = 0; i < BASE_SIZE; i++)
    {
      matrix->drawLine(startCol, ++startRow, --endCol, endRow, yellow);
      matrix->drawLine(--startCol, startRow, endCol, ++endRow, yellow);
    }
  }
  else
  {
    matrix->drawLine(startCol, startRow, endCol, endRow, off);
    for (int i = 0; i < BASE_SIZE; i++)
    {
      matrix->drawLine(startCol, ++startRow, --endCol, endRow, off);
      matrix->drawLine(--startCol, startRow, endCol, ++endRow, off);
    }
  }
}

void BaseballNR::drawBSONodes(int numNodes, int row)
{
  for (int i = 0; i < numNodes - 1; i++)
  {
    matrix->drawRect(BALL_START_COL + (i * 4), row, IND_BOX_SIZE, IND_BOX_SIZE, yellow);
  }
}

void BaseballNR::updateBases()
{
  // First base
  if (baseEncoding & 1)
  {
    drawBaseSprite(_1B_NR_COL, _1B_NR_ROW, true);
  }
  else
  {
    drawBaseSprite(_1B_NR_COL, _1B_NR_ROW, false);
  }

  // Second base
  if (baseEncoding & 2)
  {
    drawBaseSprite(_2B_NR_COL, _2B_NR_ROW, true);
  }
  else
  {
    drawBaseSprite(_2B_NR_COL, _2B_NR_ROW, false);
  }

  // Third base
  if (baseEncoding & 4)
  {
    drawBaseSprite(_3B_NR_COL, _3B_NR_ROW, true);
  }
  else
  {
    drawBaseSprite(_3B_NR_COL, _3B_NR_ROW, false);
  }
}

// Advance all baserunners 1 base via encoding then update
void BaseballNR::hitSingle()
{
  baseEncoding = baseEncoding << 1;
  baseEncoding |= 1;

  updateBases();
  checkHome();
  wipeBS();
}

// Advance all baserunners 2 bases via encoding then update
void BaseballNR::hitDouble()
{
  baseEncoding = baseEncoding << 2;
  baseEncoding |= 2;

  updateBases();
  checkHome();
  wipeBS();
}

// Advance batter to first, push all other baserunners forward
void BaseballNR::walk()
{
  int i = 0;

  if (baseEncoding == 7)
  {
    baseEncoding = baseEncoding << 1; // walk home
    baseEncoding |= 1;
  }

  else
  {
    while (((baseEncoding & (1 << i)) > 0) && (i < 3))
    {
      i++;
    }

    baseEncoding |= (1 << i);
  }

  updateBases();
  checkHome();
  wipeBS();
}

// Check if runners got home via base encoding
void BaseballNR::checkHome()
{
  int addedScore = 0;

  for (int i = 3; i < 6; i++)
  {
    // if bits 4, 5, or 6 are full, increase score and clear bit
    if ((baseEncoding & (1 << i)) > 0)
    {
      baseEncoding &= ~(1 << i); // Clear bit
      addedScore++;
    }
  }

  while (addedScore > 0)
  {
    increaseBBallScore();
    addedScore--;
  }

  baseEncoding = baseEncoding & 7; // Wipe bits above bit 3 to make sure encoding doesnt break
}

void BaseballNR::recordStrike()
{
  strikes++;

  delay(10); // I really don't know why but delays fix doubling up balls/strikes

  updateDisplayBSO();

  if (strikes >= totalStrikes)
  {
    recordOut();
    wipeBS();
  }
}

void BaseballNR::recordBall()
{
  balls++;

  delay(10);

  updateDisplayBSO();

  if (balls >= totalBalls)
  {
    walk();
    wipeBS();
  }
}

void BaseballNR::recordOut()
{
  outs++;

  delay(10);

  updateDisplayBSO();

  if (outs >= totalOuts)
  {
    outs = 0;
    baseEncoding = 0;
    updateBases();
    wipeBS();

    if (top)
    {
      top = !top;
    }
    else
    {
      top = !top;
      inning++;
    }

    drawInning();
  }
}

void BaseballNR::updateDisplayBSO()
{
  // Balls
  if (balls >= totalBalls)
  {
    for (int i = 0; i < totalBalls; i++)
    {
      matrix->drawPixel(RECORD_START_COL + (4 * i), RECORD_START_ROW, off);
    }
  }
  else
  {
    for (int i = 0; i < balls; i++)
    {
      matrix->drawPixel(RECORD_START_COL + (4 * i), RECORD_START_ROW, yellow);
    }
  }

  // Strikes
  if (strikes >= totalStrikes)
  {
    for (int i = 0; i < totalStrikes; i++)
    {
      matrix->drawPixel(RECORD_START_COL + (4 * i), RECORD_START_ROW + 7, off);
    }
  }
  else
  {
    for (int i = 0; i < strikes; i++)
    {
      matrix->drawPixel(RECORD_START_COL + (4 * i), RECORD_START_ROW + 7, yellow);
    }
  }

  // Strikes
  if (outs >= totalOuts)
  {
    for (int i = 0; i < outs; i++)
    {
      matrix->drawPixel(RECORD_START_COL + (4 * i), RECORD_START_ROW + 14, off);
    }
  }
  else
  {
    for (int i = 0; i < outs; i++)
    {
      matrix->drawPixel(RECORD_START_COL + (4 * i), RECORD_START_ROW + 14, yellow);
    }
  }
}

void BaseballNR::wipeBS()
{
  balls = totalBalls;
  strikes = totalStrikes;
  updateDisplayBSO();
  balls = 0;
  strikes = 0;
}

void BaseballNR::drawInning()
{
  if (top)
  {
    drawInningArrow(1, 3, true, false);
    drawInningArrow(1, 5, false, true);
  }
  else
  {
    drawInningArrow(1, 3, false, false);
    drawInningArrow(1, 5, true, true);
  }

  matrix->setCursor(5, 1);
  matrix->setTextColor(off);
  matrix->print(String(inning - 1));

  matrix->setCursor(5, 1);
  matrix->setTextColor(white);
  matrix->print(String(inning));
}

void BaseballNR::drawInningArrow(int startCol, int startRow, boolean turnOn, boolean invert)
{
  uint16_t color = turnOn ? yellow : off;

  if (!invert)
  {
    matrix->drawPixel(startCol, startRow, color);
    matrix->drawPixel(startCol + 1, startRow - 1, color);
    matrix->drawPixel(startCol + 2, startRow, color);
  }
  else
  {
    matrix->drawPixel(startCol, startRow, color);
    matrix->drawPixel(startCol + 1, startRow + 1, color);
    matrix->drawPixel(startCol + 2, startRow, color);
  }
}