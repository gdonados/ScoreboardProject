#ifndef CUSTOM_FRAME_H
#define CUSTOM_FRAME_H

#include "Pins.h"
#include <RGBmatrixPanel.h>
#include <SPI.h>
#include <SD.h>

#define BaseballNRFile  "bballNR.txt"

/*
 * Class to encapsulate all custom matrix generation 
 * commands for this project
 */
class CustomFrame
{
  private:
//    FrameType currentFrame;

  protected:
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
     * @brief Returns current frame
     * @return  Current frame
     */
//    FrameType getCurrentFrame(){return currentFrame;}
};

#endif
