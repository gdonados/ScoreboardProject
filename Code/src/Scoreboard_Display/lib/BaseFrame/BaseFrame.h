#ifndef BASE_FRAME_H
#define BASE_FRAME_H

#include "../../utils/Pins.h"
#include "../../utils/enumerations.h"
#include <RGBmatrixPanel.h>
#include <SPI.h>
#include <SD.h>

#define BaseballNRFile "bballNR.txt"
#define CornholeFile "chole.txt"

/*
 * Class to encapsulate all custom matrix generation
 * commands for this project
 */
class BaseFrame
{
protected:
  uint8_t redScore;
  uint8_t blueScore;

  // Main Score properties
  uint8_t redScoreCol;
  uint8_t blueScoreCol;
  uint8_t scoreRow;
  uint8_t distance;
  uint8_t leftScoreTensOffset;
  uint8_t size;

  int brightnessScalar = 1;
  int red;
  int blue;
  int yellow;
  int white;
  int off;

  RGBmatrixPanel *matrix;

  /*!
   * @brief Generates pixels on display for custom scorebugs
   * @param fileName  File name containing formatted text for
   *                  frame generation (row;col;R;G;B)
   *                  Name has 8 character limit
   */
  void displayFrame(char *fileName);

  /*!
   * @brief  Generates score
   *
   * @param col Column (x) for first number
   * @param row Row (y) for second number
   * @param textSize  size of the number
   * @param distance  distance between scores
   */
  void initScoreMain();

  /*!
   * @brief Increases score for either red or blue

   * @param redTeam      True for red, false for blue
   */
  void increaseScore(Team team);

public:
  /*!
   * @brief Constructor for custom frame handler
   *
   * @param matrix Reference to RGBmatrixPanel object
   */
  BaseFrame(RGBmatrixPanel *matrix, int redScoreCol, int scoreRow, int distance, int leftScoreTensOffset, int size, int brightnessScalar);
};

#endif
