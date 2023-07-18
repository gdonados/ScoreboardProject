#include <CustomFrame.h>
#include <SmallNumbers.h>

class Cornhole: public CustomFrame
{
  private:
    const byte SMALL_NUM_ROW     = 24;
    const byte SMALL_NUM_OFFSET  = 6;
    const byte RED_FIRSTNUM_COL  = 13;
    const byte BLUE_FIRSTNUM_COL = 52;

    /*!
     * @brief 5x5 numbers 0-9 for round scoring
     * 
     * @param value   number to draw
     * @param col     column to start
     * @param row     row to start
     * @param color   color desired to draw, 16-bit 5/6/5
     */
    void drawSmallNumber(RGBmatrixPanel matrix, int value, int col, int row, uint16_t color);

  public:
    Cornhole();

    /*!
    * @brief Generates Cornhole scoreboard static frame information and
    *         starting sprite information
    * 
    * @param matrix    Adafruit RGB matrix panel object
    */
    void displayFrame(RGBmatrixPanel matrix);

    /*!
     * @brief Increases round score for specified team
     * 
     * @param matrix    Adafruit RGB matrix panel object
     * @param redTeam   True if incresing red team, false for blue
     */
    void increaseRoundScore(RGBmatrixPanel matrix, boolean redTeam);

    /*!
     * @brief Decreases round score for specified team
     * 
     * @param matrix    Adafruit RGB matrix panel object
     * @param redTeam   True if decreasing red team, false for blue
     */
    void decreaseRoundScore(RGBmatrixPanel matrix, boolean redTeam);
};
