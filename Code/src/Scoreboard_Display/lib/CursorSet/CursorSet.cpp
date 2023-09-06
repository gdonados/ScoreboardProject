#include "CursorSet.h"

CursorSet::CursorSet(RGBmatrixPanel *matrix, int cursorCol, int cursorRow,
                     int cursorLength, int brightnessScalar, scoreboard_action action)
{
  this->matrix = matrix;
  cursorIndex = 0;
  storageIndex = 0;
  cursorInfo[storageIndex][COL_INDEX] = cursorCol;
  cursorInfo[storageIndex][ROW_INDEX] = cursorRow;
  cursorInfo[storageIndex][LENGTH_INDEX] = cursorLength;
  scoreboard_actions[storageIndex] = action;
  storageIndex++;
  this->brightnessScalar = brightnessScalar;
  cursorColor = matrix->Color888(255 / brightnessScalar, 156 / brightnessScalar, 0);
  cursorOff = matrix->Color888(0, 0, 0);
}

void CursorSet::drawCursor(int index)
{
  matrix->drawLine(cursorInfo[index][COL_INDEX],
                   cursorInfo[index][ROW_INDEX],
                   cursorInfo[index][COL_INDEX] + cursorInfo[index][LENGTH_INDEX],
                   cursorInfo[index][ROW_INDEX],
                   cursorColor);
}

void CursorSet::eraseCursor(int index)
{
  matrix->drawLine(cursorInfo[index][COL_INDEX],
                   cursorInfo[index][ROW_INDEX],
                   cursorInfo[index][COL_INDEX] + cursorInfo[index][LENGTH_INDEX],
                   cursorInfo[index][ROW_INDEX],
                   cursorOff);
}

void CursorSet::cursorSetSelect()
{
  uint8_t initialCursor = 0;
  drawCursor(initialCursor);
}

void CursorSet::cursorSetDeSelect()
{
  for (int i = 0; i <= storageIndex; i++)
  {
    eraseCursor(i);
  }
}

void CursorSet::addCursorLocation(int cursorCol, int cursorRow, int cursorLength, scoreboard_action scoreboardAction)
{
  cursorInfo[storageIndex][COL_INDEX] = cursorCol;
  cursorInfo[storageIndex][ROW_INDEX] = cursorRow;
  cursorInfo[storageIndex][LENGTH_INDEX] = cursorLength;
  scoreboard_actions[storageIndex] = scoreboardAction;
  storageIndex++;
}

void CursorSet::cursorNext()
{
  eraseCursor(cursorIndex);

  if (!(cursorIndex + 1 == storageIndex))
    cursorIndex++;

  drawCursor(cursorIndex);
}

void CursorSet::cursorPrev()
{
  eraseCursor(cursorIndex);

  if (!(cursorIndex - 1 < 0))
    cursorIndex--;

  drawCursor(cursorIndex);
}

void CursorSet::cursorConfirm()
{
  scoreboard_actions[cursorIndex]();
}