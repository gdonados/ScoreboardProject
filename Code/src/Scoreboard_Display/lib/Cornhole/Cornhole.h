#ifndef CORNHOLE_H
#define CORNHOLE_H

#include "../BaseFrame/BaseFrame.h"
#include <SmallNumbers.h>

class Cornhole : public BaseFrame
{
private:
  const byte SMALL_NUM_ROW = 24;
  const byte SMALL_NUM_OFFSET = 6;
  const byte RED_FIRSTNUM_COL = 14;
  const byte BLUE_FIRSTNUM_COL = 51;

  const uint8_t MAX_ROUND_SCORE = 12;
  const uint8_t MIN_ROUND_SCORE = 0;
  const uint8_t BUST_RESET_VALUE = 11;
  const uint8_t BUST_ROW = 9;

  const uint8_t BAR_HEIGHT = 28; // Based on current frame

  uint8_t winningScore;
  float barStep;

  // Based on current cornhole frame background
  const byte BAR_BASE_ROW = 29;
  const byte RED_BAR_BASE_COL = 2;
  const byte BLUE_BAR_BASE_COL = 60;

  uint8_t redRoundScore;
  uint8_t blueRoundScore;
  uint8_t oldRedScore;
  uint8_t oldBlueScore;

  float redComboScore;
  float blueComboScore;

  boolean doBust = true;

  /*!
   * @brief 5x5 numbers 0-9 for round scoring
   *
   * @param value   number to draw
   * @param col     column to start
   * @param row     row to start
   * @param color   color desired to draw, 16-bit 5/6/5
   */
  void drawSmallNumber(int value, int col, int row, uint16_t color);

  /**
   * @brief Increases the main score of the game,
   *          separate from CustomFrame due to progress bar placement
   *
   * @param team   Enum type for team to change
   */
  void updateMainScore();

  /**
   * @brief Increases/decreases progress bar depending on main score + round score
   */
  void updateProgressBar();

  /**
   * @brief Update frame for a bust
   *
   * @param team   Enum type for team to change
   */
  void bust(Team team);

  /**
   * @brief Display win screen for the specified team ### GEN NEW FRAME FOR THIS ###
   */

public:
  Cornhole(RGBmatrixPanel *matrix, int redScoreCol, int scoreRow, int distance, int leftScoreTensOffset, int size, int brightnessScalar);

  /*!
   * @brief Generates Cornhole scoreboard static frame information and
   *         starting sprite information
   */
  void displayFrame();

  /*!
   * @brief Increases round score for specified team
   *
   * @param team   Enum type for team to change
   */
  void increaseRoundScore(Team team);

  /*!
   * @brief Decreases round score for specified team
   *
   * @param team   Enum type for team to change
   */
  void decreaseRoundScore(Team team);

  /**
   * @brief Confirms the round scores and updates the main score
   */
  void confirmRoundScore();

  /**
   * @brief Toggles if the score gets cut in half when over
   */
  void toggleBust();
};

#endif