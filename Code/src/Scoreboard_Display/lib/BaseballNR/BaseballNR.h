#ifndef BASEBALLNR_H
#define BASEBALLNR_H

#include "CustomFrame.h"

class BaseballNR : public CustomFrame
{
private:
  byte totalBalls;
  byte totalStrikes;
  byte totalOuts;
  byte balls;
  byte strikes;
  byte outs;
  byte inning;
  boolean top;

  // Binary encoding for bases, i.e. "001" only first base
  //"110" second and third
  byte baseEncoding;

  static const int BASE_SIZE = 3; // Used for row and column calculations for filling in bases

  // Numbers gotten from current base location decisions
  static const int _1B_NR_COL = 58;
  static const int _1B_NR_ROW = 19;
  static const int _2B_NR_COL = 52;
  static const int _2B_NR_ROW = 13;
  static const int _3B_NR_COL = 46;
  static const int _3B_NR_ROW = 19;

  static const int BALL_START_COL = 30;
  static const int BALL_START_ROW = 12;
  static const int IND_BOX_SIZE = 3;
  static const int RECORD_START_COL = 31;
  static const int RECORD_START_ROW = 13;

  /*!
   * @brief Draws a "base" sprite, at one of the predefined locations
   *
   * @param startCol  Top off pixel column for empty base
   * @param startRow  Top off pixel row for empty base
   * @param turnOn    True for filling base, false for clearing
   */
  void drawBaseSprite(int startCol, int startRow, boolean turnOn);

  /*!
   * @brief Manages base sprite drawing based on game status
   */
  void updateBases();

  /*!
   * @brief Set of functions to record balls, strikes, and outs
   *
   */
  void recordOut();

  /*!
   * @brief Updates new pixels to indicate balls/strikes/out
   *
   */
  void updateDisplayBSO();

  /*!
   * @brief Wipes all ball and strike nodes
   *
   */
  void wipeBS();

  /*!
   * @brief Handles drawing inning number and top/bottom chevron
   *
   */
  void drawInning();

  /*!
   * @brief  Draws a 3 pixel inning indicator arrow
   *
   * @param startCol  Leftmost pixel column
   * @param startRow  Leftmost pixel row
   * @param turnOn    True for on, false for off
   * @param invert    True for upside down, false for rightside up
   */
  void drawInningArrow(int startCol, int startRow, boolean turnOn, boolean invert);

public:
  BaseballNR(RGBmatrixPanel *matrix, int brightnessScalar);

  /*!
   * @brief Generates all baseball scorebug information
   */
  void displayFrame();

  /*!
   * @brief Increases score for either red or blue
   *        MAY BE TEMP, DEPENDS HOW I WANT TO UPDATE SCORE
   * @param team      False for red, true for blue
   */
  void increaseScore();

  /*!
   * @brief Advances base runners up 1 base
   */
  void hitSingle();

  /*!
   * @brief Advances base runners up 2 bases
   */
  void hitDouble();

  /*!
   * @brief Advances bastter 1 base, and base runners depending on location
   */
  void walk();

  /*!
   * @brief Checks base encoding to check if baserunners got home
   */
  void checkHome();

  /*!
   * @brief Set of functions to record balls, strikes, and outs
   *
   */
  void recordStrike();
  void recordBall();
};

#endif
