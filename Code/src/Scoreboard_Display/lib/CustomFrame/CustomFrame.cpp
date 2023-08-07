#include "CustomFrame.h"

// Constructor
CustomFrame::CustomFrame(RGBmatrixPanel *matrix, int brightnessScalar)
{
  this->matrix = matrix;
  this->brightnessScalar = brightnessScalar;
  red = this->matrix->Color888(255 / brightnessScalar, 0, 0);
  blue = this->matrix->Color888(0, 128 / brightnessScalar, 224 / brightnessScalar);
  yellow = this->matrix->Color888(255 / brightnessScalar, 255 / brightnessScalar, 0);
  white = this->matrix->Color888(255 / brightnessScalar, 255 / brightnessScalar, 255 / brightnessScalar);
  off = 0;
}

// Reads from attached SD card location and RGB data of all pixels
// To draw a custom frame
// Always wipes screen
void CustomFrame::displayFrame(char *fileName)
{
  matrix->fillScreen(0); // Clear previous frame

  if (!SD.begin(SPI_CS))
  {
    Serial.println("SD init failed.");
    return;
  }

  Serial.println("Intializing done...");

  File file = SD.open(fileName);

  if (file)
  {
    while (file.available())
    {
      int row, col, r, g, b;
      String line = file.readStringUntil('\n');
      sscanf(line.c_str(), "%d;%d;%d;%d;%d", &row, &col, &r, &g, &b);

      matrix->drawPixel(col, row, matrix->Color888(r / brightnessScalar, g / brightnessScalar, b / brightnessScalar));
    }

    file.close();
  }
  else
  {
    Serial.println("Error opening file");
  }
}

// void CustomFrame::adjustBrightness(uint8_t scale)
// {
//   brightnessScale = scale;
// }
