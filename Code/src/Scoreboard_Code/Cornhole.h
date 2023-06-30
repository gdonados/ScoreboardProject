#include "Pins.h"
#include "CustomFrame.h"

const static byte small0[5][5] =
{ {1,1,1,1,1},
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,1,1,1,1}
};

const static byte small1[5][5] =
{ {0,0,1,0,0},
  {0,1,1,0,0},
  {0,0,1,0,0},
  {0,0,1,0,0},
  {0,1,1,1,1}
};

const static byte small2[5][5] =
{ {1,1,1,1,0},
  {0,0,0,0,1},
  {1,1,1,1,1},
  {1,0,0,0,0},
  {1,1,1,1,1}
};

const static byte small3[5][5] =
{ {1,1,1,1,0},
  {0,0,0,0,1},
  {0,1,1,1,0},
  {0,0,0,0,1},
  {1,1,1,1,0}
};

const static byte small4[5][5] =
{ {1,0,0,0,1},
  {1,0,0,0,1},
  {1,1,1,1,1},
  {0,0,0,0,1},
  {0,0,0,0,1}
};

const static byte small5[5][5] =
{ {1,1,1,1,1},
  {1,0,0,0,0},
  {1,1,1,1,1},
  {0,0,0,0,1},
  {1,1,1,1,0}
};

const static byte small6[5][5] =
{ {0,1,1,1,1},
  {1,0,0,0,0},
  {1,1,1,1,0},
  {1,0,0,0,1},
  {0,1,1,1,0}
};

const static byte small7[5][5] =
{ {1,1,1,1,1},
  {0,0,0,0,1},
  {0,0,0,1,0},
  {0,0,1,0,0},
  {0,1,0,0,0}
};

const static byte small8[5][5] =
{ {0,1,1,1,0},
  {1,0,0,0,1},
  {0,1,1,1,0},
  {1,0,0,0,1},
  {0,1,1,1,0}
};

const static byte small9[5][5] =
{ {0,1,1,1,0},
  {1,0,0,0,1},
  {0,1,1,1,1},
  {0,0,0,0,1},
  {0,0,0,0,1}
};

class Cornhole
{
  private:
    /*!
     * @brief 5x5 numbers 1-12 for round scoring
     * 
     * @param value   number to draw
     * @param col     column to start
     * @param row     row to start
     */
    void drawSmallNumber(RGBmatrixPanel matrix, int value, int col, int row);
    

  public:
    Cornhole();
  
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
