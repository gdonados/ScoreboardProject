#include "CustomFrame.h"

//Constructor
CustomFrame::CustomFrame()
{
  redScore = 0;
  blueScore = 0;
  currentFrame = BaseballNRMain; //Change to main menu when done
  baseEncoding = 6;
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

void CustomFrame::baseSprite(RGBmatrixPanel matrix)
{
  int startCol;
  int startRow;
  int endCol;
  int endRow;
  
  //First base
  if(baseEncoding & 1)
  {
    startCol = 58;
    startRow = 19;
    endCol = 61;
    endRow = 22;
    //Fill out second base
    matrix.drawLine(startCol, startRow, endCol, endRow, matrix.Color888(255, 255, 0));
    for(int i = 0; i < endCol-startCol; i++)
    {
      matrix.drawLine(startCol, ++startRow, --endCol, endRow, matrix.Color888(255, 255, 0));
      matrix.drawLine(--startCol, startRow, endCol, ++endRow, matrix.Color888(255, 255, 0));
    }
  }
  else
  {
    startCol = 58;
    startRow = 19;
    endCol = 61;
    endRow = 22;
    //Fill out second base
    matrix.drawLine(startCol, startRow, endCol, endRow, matrix.Color888(0, 0, 0));
    for(int i = 0; i < endCol-startCol; i++)
    {
      matrix.drawLine(startCol, ++startRow, --endCol, endRow, matrix.Color888(0, 0, 0));
      matrix.drawLine(--startCol, startRow, endCol, ++endRow, matrix.Color888(0, 0, 0));
    }
  }
  
  //Second base
  if(baseEncoding & 2)
  {
    startCol = 52;
    startRow = 13;
    endCol = 55;
    endRow = 16;
    //Fill out second base
    matrix.drawLine(startCol, startRow, endCol, endRow, matrix.Color888(255, 255, 0));
    for(int i = 0; i < endCol-startCol; i++)
    {
      matrix.drawLine(startCol, ++startRow, --endCol, endRow, matrix.Color888(255, 255, 0));
      matrix.drawLine(--startCol, startRow, endCol, ++endRow, matrix.Color888(255, 255, 0));
    }
  }
  else
  {
    startCol = 52;
    startRow = 13;
    endCol = 55;
    endRow = 16;
    //Fill out second base
    matrix.drawLine(startCol, startRow, endCol, endRow, matrix.Color888(0, 0, 0));
    for(int i = 0; i < endCol-startCol; i++)
    {
      matrix.drawLine(startCol, ++startRow, --endCol, endRow, matrix.Color888(0, 0, 0));
      matrix.drawLine(--startCol, startRow, endCol, ++endRow, matrix.Color888(0, 0, 0));
    }
  }

  //Third base
  if(baseEncoding & 4)
  {
    startCol = 46;
    startRow = 19;
    endCol = 49;
    endRow = 22;
    //Fill out second base
    matrix.drawLine(startCol, startRow, endCol, endRow, matrix.Color888(255, 255, 0));
    for(int i = 0; i < endCol-startCol; i++)
    {
      matrix.drawLine(startCol, ++startRow, --endCol, endRow, matrix.Color888(255, 255, 0));
      matrix.drawLine(--startCol, startRow, endCol, ++endRow, matrix.Color888(255, 255, 0));
    }
  }
  else
  {
    startCol = 46;
    startRow = 19;
    endCol = 49;
    endRow = 22;
    //Fill out second base
    matrix.drawLine(startCol, startRow, endCol, endRow, matrix.Color888(0, 0, 0));
    for(int i = 0; i < endCol-startCol; i++)
    {
      matrix.drawLine(startCol, ++startRow, --endCol, endRow, matrix.Color888(0, 0, 0));
      matrix.drawLine(--startCol, startRow, endCol, ++endRow, matrix.Color888(0, 0, 0));
    }
  }
}
