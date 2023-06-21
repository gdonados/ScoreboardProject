#include "Pins.h"
#include <RGBmatrixPanel.h>
#include <SPI.h>
#include <SD.h>

#define BaseballNRFile  "bballNR.txt"

enum FrameType
{
  MainMenu,
  Generic,
  CornholeOptions,
  CornholeMain,
  BaseballNROptions,
  BaseballNRMain //Baseball "No-Run"
};

/*
 * Class to encapsulate all custom matrix generation 
 * commands for this project
 */
class CustomFrame
{
  private:
    uint8_t redScore;
    uint8_t blueScore;
    
    //Binary encoding for bases, i.e. "001" only first base
    //"110" second and third
    byte baseEncoding;
    
    FrameType currentFrame;

    static const int BASE_SIZE = 3; //Used for row and column calculations for filling in bases
    
    //Numbers gotten from current base location decisions
    static const int _1B_NR_COL = 58;
    static const int _1B_NR_ROW = 19;
    static const int _2B_NR_COL = 52;
    static const int _2B_NR_ROW = 13;
    static const int _3B_NR_COL = 46;
    static const int _3B_NR_ROW = 19;
    
    /*!
     * @brief Generates pixels on display for custom scorebugs
     * @param matrix    Adafruit RGB matrix panel object
     * @param fileName  File name containing formatted text for
     *                  frame generation (row;col;R;G;B)
     *                  Name has 8 character limit
     */
    void displayFrame(RGBmatrixPanel matrix, char *fileName);

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
    
  public:
    /*!
     * @brief Constructor for custom frame handler
     */
    CustomFrame();

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
    void increaseScore(RGBmatrixPanel matrix, boolean team);

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
     * @brief Returns current frame
     * @return  Current frame
     */
    FrameType getCurrentFrame(){return currentFrame;}
};
