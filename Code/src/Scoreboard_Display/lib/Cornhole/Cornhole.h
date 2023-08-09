#include <../CustomFrame/CustomFrame.h>
#include <SmallNumbers.h>

class Cornhole : public CustomFrame
{
private:
  const byte SMALL_NUM_ROW = 24;
  const byte SMALL_NUM_OFFSET = 6;
  const byte RED_FIRSTNUM_COL = 14;
  const byte BLUE_FIRSTNUM_COL = 51;

  const uint8_t MAX_ROUND_SCORE = 12;
  const uint8_t MIN_ROUND_SCORE = 0;

  const uint8_t MAX_SCORE = 21;

  uint8_t redRoundScore;
  uint8_t blueRoundScore;
  uint8_t oldRedScore;
  uint8_t oldBlueScore;

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
  void updateProgressBar(Team team);

  /**
   * @brief Update frame for a bust
   *
   * @param team   Enum type for team to change
   */
  void bust(Team team);

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
