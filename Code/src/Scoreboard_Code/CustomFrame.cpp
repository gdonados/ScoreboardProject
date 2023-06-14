#include "CustomFrame.h"

CustomFrame::CustomFrame(RGBmatrixPanel matrix)
{
  redScore = 0;
  blueScore = 0;
}

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
