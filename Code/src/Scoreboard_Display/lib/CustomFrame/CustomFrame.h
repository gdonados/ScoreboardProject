#ifndef CUSTOM_FRAME_H
#define CUSTOM_FRAME_H

#include <Pins.h>
#include <RGBmatrixPanel.h>
#include <SPI.h>
#include <SD.h>

#define BaseballNRFile "bballNR.txt"
#define CornholeFile "chole.txt"

/*
 * Class to encapsulate all custom matrix generation
 * commands for this project
 */
class CustomFrame
{
protected:
  /*!
   * @brief Generates pixels on display for custom scorebugs
   * @param fileName  File name containing formatted text for
   *                  frame generation (row;col;R;G;B)
   *                  Name has 8 character limit
   */
  void displayFrame(char *fileName);

  uint8_t redScore;
  uint8_t blueScore;

  uint8_t redScoreCol;
  uint8_t blueScoreCol;
  uint8_t scoreRow;
  uint8_t leftScoreTensOffset;

  int brightnessScalar = 1;
  int red;
  int blue;
  int yellow;
  int white;
  int off;

  // static uint8_t brightnessScale;

  RGBmatrixPanel *matrix;

public:
  /*!
   * @brief Constructor for custom frame handler
   *
   * @param matrix Reference to RGBmatrixPanel object
   */
  CustomFrame(RGBmatrixPanel *matrix, int brightnessScalar);

  /*!
   * @brief Change brightness of display
   *
   * @param scale  Integer value to scale brightness by
   */
  //  void adjustBrightness(uint8_t scale);
};

#endif
