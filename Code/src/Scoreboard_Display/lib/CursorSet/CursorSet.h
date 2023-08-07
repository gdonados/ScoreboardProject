#include <RGBmatrixPanel.h>

/*
 * Plan is to have each cursor set have its own object to take
 * care of drawing/deleting, that way there is one cursor set
 * per frame
 *
 * "index" would be which cursor to display. Increasing the index
 * would move up or down the cursor. Driver will take care of calling
 * to remove old frame cursors
 */

class CursorSet
{
private:
  static const int DEAULT_STORAGE = 10;
  static const int COL_INDEX = 0;
  static const int ROW_INDEX = 1;
  static const int LENGTH_INDEX = 2;

  int brightnessScalar;

  byte cursorIndex; // Which cursor are we currently displaying
  byte storageIndex;
  byte cursorInfo[DEAULT_STORAGE][3];

  RGBmatrixPanel *matrix;

public:
  /*!
   * @brief Constructor for the cursor class, need an initial cursor
   *
   * @param cursorCol     Pixel column for line start
   * @param cursorRow     Pixel row for line start
   * @param cursorLength  Desired length of line
   * @param brightnessScalar  int value for scaling brightness of pixels
   */
  CursorSet(RGBmatrixPanel *matrix, int cursorCol, int cursorRow, int cursorLength, int brightnessScalar);

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
   */
  void addCursorLocation(int cursorCol, int cursorRow, int cursorLength);

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

  int getCursorIndex() { return cursorIndex; }
};
