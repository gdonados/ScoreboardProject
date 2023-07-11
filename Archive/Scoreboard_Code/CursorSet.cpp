#include "CursorSet.h"

CursorSet::CursorSet(int cursorCol, int cursorRow, int cursorLength)
{
  cursorIndex   = 0;
  storageIndex  = 0;
  cursorInfo[storageIndex][COL_INDEX]    = cursorCol;
  cursorInfo[storageIndex][ROW_INDEX]    = cursorRow;
  cursorInfo[storageIndex][LENGTH_INDEX] = cursorLength;
  storageIndex++;
}

void CursorSet::cursorSetSelect(RGBmatrixPanel matrix)
{
  matrix.drawLine(cursorInfo[0][COL_INDEX], cursorInfo[0][ROW_INDEX], cursorInfo[0][COL_INDEX]+cursorInfo[0][LENGTH_INDEX], 
    cursorInfo[0][ROW_INDEX], matrix.Color888(255, 156, 0));
}

void CursorSet::cursorSetDeSelect(RGBmatrixPanel matrix)
{
  for(int i = 0; i <= storageIndex; i++)
  {
    matrix.drawLine(cursorInfo[i][COL_INDEX], cursorInfo[i][ROW_INDEX], cursorInfo[i][COL_INDEX]+cursorInfo[i][LENGTH_INDEX], 
      cursorInfo[i][ROW_INDEX], matrix.Color888(0, 0, 0));
  }
}

void CursorSet::addCursorLocation(int cursorCol, int cursorRow, int cursorLength)
{
  cursorInfo[storageIndex][COL_INDEX]    = cursorCol;
  cursorInfo[storageIndex][ROW_INDEX]    = cursorRow;
  cursorInfo[storageIndex][LENGTH_INDEX] = cursorLength;
  storageIndex++;
}

void CursorSet::cursorNext(RGBmatrixPanel matrix)
{
  matrix.drawLine(cursorInfo[cursorIndex][COL_INDEX], cursorInfo[cursorIndex][ROW_INDEX], cursorInfo[cursorIndex][COL_INDEX]+cursorInfo[cursorIndex][LENGTH_INDEX], 
    cursorInfo[cursorIndex][ROW_INDEX], matrix.Color888(0, 0, 0));

  if(!(cursorIndex+1 == storageIndex))
    cursorIndex++;

  matrix.drawLine(cursorInfo[cursorIndex][COL_INDEX], cursorInfo[cursorIndex][ROW_INDEX], cursorInfo[cursorIndex][COL_INDEX]+cursorInfo[cursorIndex][LENGTH_INDEX], 
    cursorInfo[cursorIndex][ROW_INDEX], matrix.Color888(255, 156, 0));
}

void CursorSet::cursorPrev(RGBmatrixPanel matrix)
{
  matrix.drawLine(cursorInfo[cursorIndex][COL_INDEX], cursorInfo[cursorIndex][ROW_INDEX], cursorInfo[cursorIndex][COL_INDEX]+cursorInfo[cursorIndex][LENGTH_INDEX], 
    cursorInfo[cursorIndex][ROW_INDEX], matrix.Color888(0, 0, 0));

  if(!(cursorIndex-1 < 0))
    cursorIndex--;

  matrix.drawLine(cursorInfo[cursorIndex][COL_INDEX], cursorInfo[cursorIndex][ROW_INDEX], cursorInfo[cursorIndex][COL_INDEX]+cursorInfo[cursorIndex][LENGTH_INDEX], 
    cursorInfo[cursorIndex][ROW_INDEX], matrix.Color888(255, 156, 0));
}
