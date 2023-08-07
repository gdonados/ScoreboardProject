#include "CursorSet.h"

CursorSet::CursorSet(RGBmatrixPanel *matrix, int cursorCol, int cursorRow, int cursorLength, int brightnessScalar)
{
  this->matrix = matrix;
  cursorIndex = 0;
  storageIndex = 0;
  cursorInfo[storageIndex][COL_INDEX] = cursorCol;
  cursorInfo[storageIndex][ROW_INDEX] = cursorRow;
  cursorInfo[storageIndex][LENGTH_INDEX] = cursorLength;
  storageIndex++;
  this->brightnessScalar = brightnessScalar;
}

void CursorSet::cursorSetSelect()
{
  matrix->drawLine(cursorInfo[0][COL_INDEX], cursorInfo[0][ROW_INDEX], cursorInfo[0][COL_INDEX] + cursorInfo[0][LENGTH_INDEX],
                   cursorInfo[0][ROW_INDEX], matrix->Color888(255 / brightnessScalar, 156 / brightnessScalar, 0));
}

void CursorSet::cursorSetDeSelect()
{
  for (int i = 0; i <= storageIndex; i++)
  {
    matrix->drawLine(cursorInfo[i][COL_INDEX], cursorInfo[i][ROW_INDEX], cursorInfo[i][COL_INDEX] + cursorInfo[i][LENGTH_INDEX],
                     cursorInfo[i][ROW_INDEX], matrix->Color888(0, 0, 0));
  }
}

void CursorSet::addCursorLocation(int cursorCol, int cursorRow, int cursorLength)
{
  cursorInfo[storageIndex][COL_INDEX] = cursorCol;
  cursorInfo[storageIndex][ROW_INDEX] = cursorRow;
  cursorInfo[storageIndex][LENGTH_INDEX] = cursorLength;
  storageIndex++;
}

void CursorSet::cursorNext()
{
  matrix->drawLine(cursorInfo[cursorIndex][COL_INDEX], cursorInfo[cursorIndex][ROW_INDEX], cursorInfo[cursorIndex][COL_INDEX] + cursorInfo[cursorIndex][LENGTH_INDEX],
                   cursorInfo[cursorIndex][ROW_INDEX], matrix->Color888(0, 0, 0));

  if (!(cursorIndex + 1 == storageIndex))
    cursorIndex++;

  matrix->drawLine(cursorInfo[cursorIndex][COL_INDEX], cursorInfo[cursorIndex][ROW_INDEX], cursorInfo[cursorIndex][COL_INDEX] + cursorInfo[cursorIndex][LENGTH_INDEX],
                   cursorInfo[cursorIndex][ROW_INDEX], matrix->Color888(255 / brightnessScalar, 156 / brightnessScalar, 0));
}

void CursorSet::cursorPrev()
{
  matrix->drawLine(cursorInfo[cursorIndex][COL_INDEX], cursorInfo[cursorIndex][ROW_INDEX], cursorInfo[cursorIndex][COL_INDEX] + cursorInfo[cursorIndex][LENGTH_INDEX],
                   cursorInfo[cursorIndex][ROW_INDEX], matrix->Color888(0, 0, 0));

  if (!(cursorIndex - 1 < 0))
    cursorIndex--;

  matrix->drawLine(cursorInfo[cursorIndex][COL_INDEX], cursorInfo[cursorIndex][ROW_INDEX], cursorInfo[cursorIndex][COL_INDEX] + cursorInfo[cursorIndex][LENGTH_INDEX],
                   cursorInfo[cursorIndex][ROW_INDEX], matrix->Color888(255 / brightnessScalar, 156 / brightnessScalar, 0));
}
