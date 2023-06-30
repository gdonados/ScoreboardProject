#include "Cornhole.h"

Cornhole::Cornhole()
{
}

void Cornhole::drawSmallNumber(RGBmatrixPanel matrix, int value, int col, int row)
{
  uint16_t color;
  
  row ? color = matrix.Color333(7, 0, 0) : color = matrix.Color333(0, 4, 7);
  
  switch(value)
  {
    case 0:
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; i < 5; i++)
        {
          if(small0[i][j] == 1)
            matrix.drawPixel(col+i, row+j, color); //darker for testing
        }
      }
      break;

    case 1:
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; i < 5; i++)
        {
          if(small1[i][j] == 1)
            matrix.drawPixel(col+i, row+j, color); //darker for testing
        }
      }
      break;

    case 2:
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; i < 5; i++)
        {
          if(small2[i][j] == 1)
            matrix.drawPixel(col+i, row+j, color); //darker for testing
        }
      }
      break;

    case 3:
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; i < 5; i++)
        {
          if(small3[i][j] == 1)
            matrix.drawPixel(col+i, row+j, color); //darker for testing
        }
      }
      break;

    case 4:
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; i < 5; i++)
        {
          if(small4[i][j] == 1)
            matrix.drawPixel(col+i, row+j, color); //darker for testing
        }
      }
      break;

    case 5:
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; i < 5; i++)
        {
          if(small5[i][j] == 1)
            matrix.drawPixel(col+i, row+j, color); //darker for testing
        }
      }
      break;

    case 6:
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; i < 5; i++)
        {
          if(small6[i][j] == 1)
            matrix.drawPixel(col+i, row+j, color); //darker for testing
        }
      }
      break;

    case 7:
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; i < 5; i++)
        {
          if(small7[i][j] == 1)
            matrix.drawPixel(col+i, row+j, color); //darker for testing
        }
      }
      break;

    case 8:
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; i < 5; i++)
        {
          if(small8[i][j] == 1)
            matrix.drawPixel(col+i, row+j, color); //darker for testing
        }
      }
      break;

    case 9:
      for(int i = 0; i < 5; i++)
      {
        for(int j = 0; i < 5; i++)
        {
          if(small9[i][j] == 1)
            matrix.drawPixel(col+i, row+j, color); //darker for testing
        }
      }
      break;
  }
}

void Cornhole::increaseRoundScore(RGBmatrixPanel matrix, boolean redTeam)
{
  
}

void Cornhole::decreaseRoundScore(RGBmatrixPanel matrix, boolean redTeam)
{
  
}
