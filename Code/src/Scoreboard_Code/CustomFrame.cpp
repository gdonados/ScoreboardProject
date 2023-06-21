#include "CustomFrame.h"

//Constructor
CustomFrame::CustomFrame()
{
  redScore = 0;
  blueScore = 0;
  baseEncoding = 0;
  currentFrame = BaseballNRMain; //Change to main menu when done
}

//Reads from attached SD card location and RGB data of all pixels
//To draw a custom frame
//Always wipes screen
void CustomFrame::displayFrame(RGBmatrixPanel matrix, char *fileName)
{
  matrix.fillScreen(0); //Clear previous frame
  
  if(!SD.begin(SPI_CS))
  {
    Serial.println("SD init failed.");
    return;
  }

  Serial.println("Intializing done...");
  
  File file = SD.open(fileName);

  if(file)
  {
    while(file.available())
    {
      int row, col, r, g, b;
      String line = file.readStringUntil('\n');
      sscanf(line.c_str(), "%d;%d;%d;%d;%d", &row, &col, &r, &g, &b);

      matrix.drawPixel(col, row, matrix.Color888(r/3,g/3,b/3)); //darker for testing
    }

    file.close();
  }
  else
  {
    Serial.println("Error opening file");
  }
}

//Bundeled commands for generated baseball no run scorebug
void CustomFrame::genBaseballNR(RGBmatrixPanel matrix)
{
  displayFrame(matrix, BaseballNRFile);

  //Red set
  matrix.setCursor(20,1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(String(0));

  //Blue set
  matrix.setCursor(39,1);
  matrix.setTextColor(matrix.Color333(0, 4, 7));
  matrix.print(String(0));
}

//Increases red or blue score
//Currently need switch for frame selecting, due to scores being in different spots
void CustomFrame::increaseScore(RGBmatrixPanel matrix, boolean team)
{
  switch(currentFrame)
  {
    case BaseballNRMain:
      if(!team)
      {
        //Erase old score
        redScore >= 10 ? matrix.setCursor(14,1) : matrix.setCursor(20,1);
       
        matrix.setTextColor(matrix.Color333(0, 0, 0));
        matrix.print(String(redScore));
        redScore++;

        //Not future-proofed for scores > 99
        redScore >= 10 ? matrix.setCursor(14,1) : matrix.setCursor(20,1);

        matrix.setTextColor(matrix.Color333(7, 0, 0));
        matrix.print(String(redScore));
      }
      else
      {
        //Erase old score
        matrix.setCursor(39,1);
        matrix.setTextColor(matrix.Color333(0, 0, 0));
        matrix.print(String(blueScore));
        blueScore++;
        matrix.setCursor(39,1);
        matrix.setTextColor(matrix.Color333(0, 4, 7));
        matrix.print(String(blueScore));
      }
      break;

      
  }
}

void CustomFrame::drawBaseSprite(RGBmatrixPanel matrix, int startCol, int startRow, boolean turnOn)
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

void CustomFrame::updateBases(RGBmatrixPanel matrix)
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
void CustomFrame::hitSingle(RGBmatrixPanel matrix)
{
  baseEncoding = baseEncoding << 1;
  baseEncoding |= 1;

  updateBases(matrix);
  checkHome(matrix);
}

//Advance all baserunners 2 bases via encoding then update
void CustomFrame::hitDouble(RGBmatrixPanel matrix)
{
  baseEncoding = baseEncoding << 2;
  baseEncoding |= 2;

  updateBases(matrix);
  checkHome(matrix);
}

//Advance batter to first, push all other baserunners forward
void CustomFrame::walk(RGBmatrixPanel matrix)
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
}

//Check if runners got home via base encoding
void CustomFrame::checkHome(RGBmatrixPanel matrix)
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
    increaseScore(matrix, false); //NEED TO DECIDE EITHER MANUAL SWITCH OR AUTO
    addedScore--;
  }

  baseEncoding = baseEncoding & 7; //Wipe bits above bit 3 to make sure encoding doesnt break 
}
