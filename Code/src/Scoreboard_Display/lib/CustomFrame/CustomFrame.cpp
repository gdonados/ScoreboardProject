#include "CustomFrame.h"

// Constructor
CustomFrame::CustomFrame(RGBmatrixPanel *matrix, int redScoreCol, int scoreRow, int distance, int leftScoreTensOffset, int size, int brightnessScalar)
{
  this->matrix = matrix;

  this->brightnessScalar = brightnessScalar;
  red = this->matrix->Color888(255 / brightnessScalar, 0, 0);
  blue = this->matrix->Color888(0, 128 / brightnessScalar, 224 / brightnessScalar);
  yellow = this->matrix->Color888(255 / brightnessScalar, 255 / brightnessScalar, 0);
  white = this->matrix->Color888(255 / brightnessScalar, 255 / brightnessScalar, 255 / brightnessScalar);
  off = 0;

  this->distance = distance;
  this->redScoreCol = redScoreCol;
  blueScoreCol = redScoreCol + distance;
  this->scoreRow = scoreRow;
  this->size = size;
  this->leftScoreTensOffset = leftScoreTensOffset;
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

void CustomFrame::initScoreMain()
{
  redScore = 0;
  blueScore = 0;

  // Red
  matrix->setCursor(redScoreCol, scoreRow);
  matrix->setTextSize(size);
  matrix->setTextColor(red);
  matrix->print(String(redScore));

  // Blue
  matrix->setCursor(blueScoreCol, scoreRow);
  matrix->setTextSize(size);
  matrix->setTextColor(blue);
  matrix->print(String(blueScore));
}

void CustomFrame::increaseScore(Team team)
{
  uint16_t color = team == REDTEAM ? red : blue;
  uint8_t &score = team == REDTEAM ? redScore : blueScore;
  uint8_t col = team == REDTEAM ? redScoreCol : blueScoreCol;

  // Erase old score
  (score >= 10 && team == REDTEAM) ? matrix->setCursor(col - leftScoreTensOffset, scoreRow) : matrix->setCursor(col, scoreRow);

  matrix->setTextColor(off);
  matrix->print(String(score));
  score++;

  // Not future-proofed for scores > 99
  (score >= 10 && team == REDTEAM) ? matrix->setCursor(col - leftScoreTensOffset, scoreRow) : matrix->setCursor(col, scoreRow);

  matrix->setTextColor(color);
  matrix->print(String(score));
}