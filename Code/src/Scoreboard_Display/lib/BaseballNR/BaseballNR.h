#ifndef BASEBALLNR_H
#define BASEBALLNR_H

#include "Pins.h"
#include "CustomFrame.h"

class BaseballNR: public CustomFrame
{
  private:
    uint8_t redScore;
    uint8_t blueScore;
    byte    totalBalls;
    byte    totalStrikes;
    byte    totalOuts;
    byte    balls;
    byte    strikes;
    byte    outs;
    byte    inning;
    boolean top;

    //Binary encoding for bases, i.e. "001" only first base
    //"110" second and third
    byte baseEncoding;

    static const int BASE_SIZE = 3; //Used for row and column calculations for filling in bases
    
    //Numbers gotten from current base location decisions
    static const int _1B_NR_COL = 58;
    static const int _1B_NR_ROW = 19;
    static const int _2B_NR_COL = 52;
    static const int _2B_NR_ROW = 13;
    static const int _3B_NR_COL = 46;
    static const int _3B_NR_ROW = 19;

    static const int BALL_START_COL   = 30;
    static const int BALL_START_ROW   = 12;
    static const int IND_BOX_SIZE     = 3;
    static const int RECORD_START_COL = 31;
    static const int RECORD_START_ROW = 13;

    /*!
     * @brief Draws a "base" sprite, at one of the predefined locations
     * 
     * @param matrix    Adafruit RGB matrix panel object
     * @param startCol  Top off pixel column for empty base
     * @param startRow  Top off pixel row for empty base  
     * @param turnOn    True for filling base, false for clearing
     */
    void drawBaseSprite(RGBmatrixPanel matrix, int startCol, int startRow, boolean turnOn);

    /*!
     * @brief Manages base sprite drawing based on game status
     * @param matrix    Adafruit RGB matrix panel object
     */
    void updateBases(RGBmatrixPanel matrix);

    /*!
     * @brief Set of functions to record balls, strikes, and outs
     * 
     * @param matrix    Adafruit RGB matrix panel object
     */
    void recordOut(RGBmatrixPanel matrix);

    /*!
     * @brief Updates new pixels to indicate balls/strikes/out
     * 
     * @param matrix    Adafruit RGB matrix panel object
     */
    void updateDisplayBSO(RGBmatrixPanel matrix);

    /*!
     * @brief Wipes all ball and strike nodes
     * 
     * @param matrix    Adafruit RGB matrix panel object
     */
    void wipeBS(RGBmatrixPanel matrix);

    /*!
     * @brief Handles drawing inning number and top/bottom chevron
     * 
     * @param matrix    Adafruit RGB matrix panel object
     */
    void drawInning(RGBmatrixPanel matrix);

  public:

    BaseballNR();
  
    /*!
     * @brief Generates all baseball scorebug information
     * @param matrix    Adafruit RGB matrix panel object
     */
    void genBaseballNR(RGBmatrixPanel matrix);

    /*!
     * @brief Increases score for either red or blue
     *        MAY BE TEMP, DEPENDS HOW I WANT TO UPDATE SCORE
     * @param matrix    Adafruit RGB matrix panel object
     * @param team      False for red, true for blue
     */
    void increaseScore(RGBmatrixPanel matrix);

    /*!
     * @brief Advances base runners up 1 base
     * @param matrix    Adafruit RGB matrix panel object
     */
    void hitSingle(RGBmatrixPanel matrix);

    /*!
     * @brief Advances base runners up 2 bases
     * @param matrix    Adafruit RGB matrix panel object
     */
    void hitDouble(RGBmatrixPanel matrix);

    /*!
     * @brief Advances bastter 1 base, and base runners depending on location
     * @param matrix    Adafruit RGB matrix panel object
     */
    void walk(RGBmatrixPanel matrix);

    /*!
     * @brief Checks base encoding to check if baserunners got home
     */
    void checkHome(RGBmatrixPanel matrix);

    /*!
     * @brief Set of functions to record balls, strikes, and outs
     * 
     * @param matrix    Adafruit RGB matrix panel object
     */
    void recordStrike(RGBmatrixPanel matrix);
    void recordBall(RGBmatrixPanel matrix);

};

#endif
