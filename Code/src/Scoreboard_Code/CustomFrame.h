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
   
    /*!
     * @brief Generates pixels on display for custom scorebugs
     * @param matrix    Adafruit RGB matrix panel object
     * @param fileName  File name containing formatted text for
     *                  frame generation (row;col;R;G;B)
     *                  Name has 8 character limit
     */
    void displayFrame(RGBmatrixPanel matrix, char *fileName);
    
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
     * @brief Draws a "base" sprite, at one of the predefined locations
     * @param matrix    Adafruit RGB matrix panel object
     */
     //Should be private eventually
    void baseSprite(RGBmatrixPanel matrix);

    /*!
     * @brief Returns current frame
     * @return  Current frame
     */
    FrameType getCurrentFrame(){return currentFrame;}
};
