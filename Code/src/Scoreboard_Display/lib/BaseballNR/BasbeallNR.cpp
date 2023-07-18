#include "BaseballNR.h"

BaseballNR::BaseballNR()
{
  leftScoreTensOffset = 6;
  redScore      = 0;
  blueScore     = 0;
  redScoreCol   = 20;
  blueScoreCol  = 39;
  inning        = 1;
  top           = true;
}

//Bundeled commands for generated baseball no run scorebug
void BaseballNR::displayFrame(RGBmatrixPanel matrix)
{
  CustomFrame::displayFrame(matrix, BaseballNRFile);

  //defaults
  baseEncoding  = 0;
  totalBalls    = 4;
  totalStrikes  = 3;
  totalOuts     = 3;

  balls         = 0;
  strikes       = 0;
  outs          = 0;

  //Red set
  matrix.setCursor(redScoreCol,scoreRow);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(String(0));

  //Blue set
  matrix.setCursor(blueScoreCol,scoreRow);
  matrix.setTextColor(matrix.Color333(0, 4, 7));
  matrix.print(String(0));
  
  //Balls
  for(int i = 0; i < totalBalls-1; i++)
  {
    matrix.drawRect(BALL_START_COL+(i*4), BALL_START_ROW, IND_BOX_SIZE, IND_BOX_SIZE, matrix.Color333(7, 7, 0));
  }

  //Strikes
  for(int i = 0; i < totalStrikes-1; i++)
  {
    matrix.drawRect(BALL_START_COL+(i*4), BALL_START_ROW+7, IND_BOX_SIZE, IND_BOX_SIZE, matrix.Color333(7, 7, 0));
  }

  //Outs
  for(int i = 0; i < totalStrikes-1; i++)
  {
    matrix.drawRect(BALL_START_COL+(i*4), BALL_START_ROW+14, IND_BOX_SIZE, IND_BOX_SIZE, matrix.Color333(7, 7, 0));
  }

  //Innings
  drawInning(matrix);
}

//Increases red or blue score
//Currently need switch for frame selecting, due to scores being in different spots
void BaseballNR::increaseScore(RGBmatrixPanel matrix)
{
  uint16_t colorOff = matrix.Color333(0, 0, 0);
  uint16_t color;
  top ? color = matrix.Color333(7, 0, 0) : color = matrix.Color333(0, 4, 7);

  if(top)
  {
    //Erase old score
    redScore >= 10 ? matrix.setCursor(redScoreCol - leftScoreTensOffset,scoreRow) : matrix.setCursor(redScoreCol,scoreRow);
   
    matrix.setTextColor(colorOff);
    matrix.print(String(redScore));
    redScore++;

    //Not future-proofed for scores > 99
    redScore >= 10 ? matrix.setCursor(redScoreCol - leftScoreTensOffset,scoreRow) : matrix.setCursor(redScoreCol,scoreRow);

    matrix.setTextColor(color);
    matrix.print(String(redScore));
  }
  else
  {
    //Erase old score
    matrix.setCursor(blueScoreCol,scoreRow);
    matrix.setTextColor(colorOff);
    matrix.print(String(blueScore));
    blueScore++;
    matrix.setCursor(blueScoreCol,scoreRow);
    matrix.setTextColor(color);
    matrix.print(String(blueScore));
  }
}

void BaseballNR::drawBaseSprite(RGBmatrixPanel matrix, int startCol, int startRow, boolean turnOn)
{
  int endCol = startCol + BASE_SIZE;
  int endRow = startRow + BASE_SIZE;

  if(turnOn)
  {
    //Fill out base
    matrix.drawLine(startCol, startRow, endCol, endRow, matrix.Color888(255, 255, 0));
    for(int i = 0; i < BASE_SIZE; i++)
    {
      matrix.drawLine(startCol, ++startRow, --endCol, endRow, matrix.Color888(255, 255, 0));
      matrix.drawLine(--startCol, startRow, endCol, ++endRow, matrix.Color888(255, 255, 0));
    }
  }
  else
  {
    matrix.drawLine(startCol, startRow, endCol, endRow, matrix.Color888(0, 0, 0));
    for(int i = 0; i < BASE_SIZE; i++)
    {
      matrix.drawLine(startCol, ++startRow, --endCol, endRow, matrix.Color888(0, 0, 0));
      matrix.drawLine(--startCol, startRow, endCol, ++endRow, matrix.Color888(0, 0, 0));
    }
  }
}

void BaseballNR::updateBases(RGBmatrixPanel matrix)
{
  //First base
  if(baseEncoding & 1)
  {
    drawBaseSprite(matrix, _1B_NR_COL, _1B_NR_ROW, true);
  }
  else
  {
    drawBaseSprite(matrix, _1B_NR_COL, _1B_NR_ROW, false);
  }
  
  //Second base
  if(baseEncoding & 2)
  {
    drawBaseSprite(matrix, _2B_NR_COL, _2B_NR_ROW, true);
  }
  else
  {
    drawBaseSprite(matrix, _2B_NR_COL, _2B_NR_ROW, false);
  }

  //Third base
  if(baseEncoding & 4)
  {
    drawBaseSprite(matrix, _3B_NR_COL, _3B_NR_ROW, true);
  }
  else
  {
    drawBaseSprite(matrix, _3B_NR_COL, _3B_NR_ROW, false);
  }
}

//Advance all baserunners 1 base via encoding then update
void BaseballNR::hitSingle(RGBmatrixPanel matrix)
{
  baseEncoding = baseEncoding << 1;
  baseEncoding |= 1;

  updateBases(matrix);
  checkHome(matrix);
  wipeBS(matrix);
}

//Advance all baserunners 2 bases via encoding then update
void BaseballNR::hitDouble(RGBmatrixPanel matrix)
{
  baseEncoding = baseEncoding << 2;
  baseEncoding |= 2;

  updateBases(matrix);
  checkHome(matrix);
  wipeBS(matrix);
}

//Advance batter to first, push all other baserunners forward
void BaseballNR::walk(RGBmatrixPanel matrix)
{
  int i = 0;

  if(baseEncoding == 7)
  {
    baseEncoding = baseEncoding<<1; //walk home
    baseEncoding |= 1;
  }

  else
  {
    while(((baseEncoding & (1<<i)) > 0) && (i < 3))
    {
      i++;
    } 
  
    baseEncoding |= (1<<i);
  }
  
  updateBases(matrix);
  checkHome(matrix);
  wipeBS(matrix);
}

//Check if runners got home via base encoding
void BaseballNR::checkHome(RGBmatrixPanel matrix)
{
  int addedScore = 0;
  
  for(int i = 3; i < 6; i++)
  {
    //if bits 4, 5, or 6 are full, increase score and clear bit
    if((baseEncoding & (1<<i)) > 0)
    {
      baseEncoding &= ~(1<<i); //Clear bit
      addedScore++;
    }
  }

  while(addedScore > 0)
  {
    increaseScore(matrix); //NEED TO DECIDE EITHER MANUAL SWITCH OR AUTO
    addedScore--;
  }

  baseEncoding = baseEncoding & 7; //Wipe bits above bit 3 to make sure encoding doesnt break 
}

void BaseballNR::recordStrike(RGBmatrixPanel matrix)
{
  strikes++;

  delay(10); //I really don't know why but delays fix doubling up balls/strikes

  updateDisplayBSO(matrix);

  if(strikes >= totalStrikes)
  {
    recordOut(matrix);
    wipeBS(matrix);
  }
}

void BaseballNR::recordBall(RGBmatrixPanel matrix)
{
  balls++;

  delay(10);

  updateDisplayBSO(matrix);

  if(balls >= totalBalls)
  {
    walk(matrix);
    wipeBS(matrix);
  }
}

void BaseballNR::recordOut(RGBmatrixPanel matrix)
{
  outs++;

  delay(10);

  updateDisplayBSO(matrix);

  if(outs >= totalOuts)
  {
    outs = 0;
    baseEncoding = 0;
    updateBases(matrix);
    wipeBS(matrix);

    if(top)
    {
      top = !top;
    }
    else
    {
      top = !top;
      inning++;
    }

    drawInning(matrix);
  }
}

void BaseballNR::updateDisplayBSO(RGBmatrixPanel matrix)
{
  //Balls
  if(balls >= totalBalls)
  {
    for(int i = 0; i < totalBalls; i++)
    {
      matrix.drawPixel(RECORD_START_COL+(4*i), RECORD_START_ROW, matrix.Color333(0,0,0));
    }
  }
  else
  {
    for(int i = 0; i < balls; i++)
    {
      matrix.drawPixel(RECORD_START_COL+(4*i), RECORD_START_ROW, matrix.Color333(7,7,0));
    }
  }

  //Strikes
  if(strikes >= totalStrikes)
  {
    for(int i = 0; i < totalStrikes; i++)
    {
      matrix.drawPixel(RECORD_START_COL+(4*i), RECORD_START_ROW+7, matrix.Color333(0,0,0));
    }
  }
  else
  {
    for(int i = 0; i < strikes; i++)
    {
      matrix.drawPixel(RECORD_START_COL+(4*i), RECORD_START_ROW+7, matrix.Color333(7,7,0));
    }
  }

  //Strikes
  if(outs >= totalOuts)
  {
    for(int i = 0; i < outs; i++)
    {
      matrix.drawPixel(RECORD_START_COL+(4*i), RECORD_START_ROW+14, matrix.Color333(0,0,0));
    }
  }
  else
  {
    for(int i = 0; i < outs; i++)
    {
      matrix.drawPixel(RECORD_START_COL+(4*i), RECORD_START_ROW+14, matrix.Color333(7,7,0));
    }
  }
}

void BaseballNR::wipeBS(RGBmatrixPanel matrix)
{
  balls = totalBalls;
  strikes = totalStrikes;
  updateDisplayBSO(matrix);
  balls = 0;
  strikes = 0;
}

void BaseballNR::drawInning(RGBmatrixPanel matrix)
{
  if(top)
  {
    matrix.drawPixel(2, 2, matrix.Color333(7,7,0));
    matrix.drawPixel(1, 3, matrix.Color333(7,7,0));
    matrix.drawPixel(3, 3, matrix.Color333(7,7,0));

    matrix.drawPixel(2, 6, matrix.Color333(0,0,0));
    matrix.drawPixel(1, 5, matrix.Color333(0,0,0));
    matrix.drawPixel(3, 5, matrix.Color333(0,0,0));
  }
  else
  {
    matrix.drawPixel(2, 6, matrix.Color333(7,7,0));
    matrix.drawPixel(1, 5, matrix.Color333(7,7,0));
    matrix.drawPixel(3, 5, matrix.Color333(7,7,0));

    matrix.drawPixel(2, 2, matrix.Color333(0,0,0));
    matrix.drawPixel(1, 3, matrix.Color333(0,0,0));
    matrix.drawPixel(3, 3, matrix.Color333(0,0,0));
  }

  matrix.setCursor(5,1);
  matrix.setTextColor(matrix.Color333(0, 0, 0));
  matrix.print(String(inning-1));

  matrix.setCursor(5,1);
  matrix.setTextColor(matrix.Color333(7, 7, 7));
  matrix.print(String(inning));
}
