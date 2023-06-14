// Contains instructions for managing custom frames and sprites
// A "frame" is anything major and unchanging, like certain text or separators
// A "sprite" would be something that changes, like the actual score
  // or, in the case of BaseballNR, bases being filled in
// Formatted as follows: row;col;R;G;Bw
// FILE NAMES ARE 8 CHARACTERS MAX

#include "Pins.h"
#include <RGBmatrixPanel.h>
#include <SPI.h>
#include <SD.h>

enum FrameType
{
  MainMenu,
  Generic,
  CornholeOptions,
  CornholeMain,
  BaseballNROptions,
  BaseballNRMain //Baseball "No-Run"
};

class CustomFrame
{
  private:
    uint8_t redScore;
    uint8_t blueScore;
    
  public:
    CustomFrame(RGBmatrixPanel matrix);
    void displayFrame(RGBmatrixPanel matrix, char *fileName);
};
