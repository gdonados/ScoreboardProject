#ifndef CURSORSET_H
#define CURSORSET_H

#include <RGBmatrixPanel.h>

// ##NEXT TASK MAKE CALLBACKS
typedef void (*scoreboard_action)();

class CursorSet
{
private:
  static const int DEFAULT_STORAGE = 10;
  static const int COL_INDEX = 0;
  static const int ROW_INDEX = 1;
  static const int LENGTH_INDEX = 2;

  int brightnessScalar;
  int cursorColor;
  int cursorOff;

  byte cursorIndex; // Which cursor are we currently displaying
  byte storageIndex;
  byte cursorInfo[DEFAULT_STORAGE][3]; // Column = 1, row = 2, length = 3

  scoreboard_action scoreboard_actions[DEFAULT_STORAGE];

  RGBmatrixPanel *matrix;

  /**
   * @brief Draws new cursor line
   *
   * @param index Index of stored cursor information
   */
  void drawCursor(int index);

  /**
   * @brief Erases cursor line
   *
   * @param index Index of stored cursor information
   */
  void eraseCursor(int index);

public:
  /*!
   * @brief Constructor for the cursor class, need an initial cursor
   *
   * @param cursorCol     Pixel column for line start
   * @param cursorRow     Pixel row for line start
   * @param cursorLength  Desired length of line
   * @param brightnessScalar  int value for scaling brightness of pixels
   * @param scoreboardAction  Function address of action to be taken
   */
  CursorSet(RGBmatrixPanel *matrix, int cursorCol, int cursorRow, int cursorLength, int brightnessScalar, scoreboard_action action);

  /*!
   * @brief Sets first cursor for this cursor set
   *
   * @param matrix    Adafruit RGB matrix panel object
   */
  void cursorSetSelect();

  /*!
   * @brief De-select this cursor set, wipe all cursor locations
   *
   * @param matrix    Adafruit RGB matrix panel object
   */
  void cursorSetDeSelect();

  /*!
   * @brief Adds a new cursor location and size to this cursor set
   *
   * @param cursorCol     Pixel column for line start
   * @param cursorRow     Pixel row for line start
   * @param cursorLength  Desired length of line
   * @param scoreboardAction  Function address of action to be taken
   */
  void addCursorLocation(int cursorCol, int cursorRow, int cursorLength, scoreboard_action scoreboardAction);

  /*!
   * @brief Advance to the next cursor in this cursor set
   *
   * @param matrix    Adafruit RGB matrix panel object
   */
  void cursorNext();

  /*!
   * @brief Retreat to previous cursor in this cursor set
   *
   * @param matrix    Adafruit RGB matrix panel object
   */
  void cursorPrev();

  /**
   * @brief Runs stored callback function for cursor index
   */
  void cursorConfirm();

  int getCursorIndex() { return cursorIndex; }
};

#endif