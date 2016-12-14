#ifndef AI_H__
#define AI_H__

#include "board.h"

/**
 * Requires: nothing.
 * Modifies: nothing.
 * Effects: Chooses a column for the next move
 *          and returns the column index. The
 *          return value must be in range
 *          [0, NUM_COLS-1].
 */
int connect4AI(const Board& board);

bool threeInCol(const Board& board, int colIndex, PieceType player);

bool checkForChipBelowEmpty(const Board& board, int col, int row);

int threeInRowRightEmpty(const Board& board, int rowIndex, PieceType player);

int deathMark_a(const Board& board, PieceType player);

int deathMark_b(const Board& board, PieceType player);

int threeInRowRightAngleEmpty_right(const Board& board, PieceType player);

int threeInRowRightAngleEmpty_left(const Board& board, PieceType player);

int findEmptyCol(const Board& board);

int twoInRowRightAngleEmpty_left(const Board& board, PieceType player);

int twoInRowRightAngleEmpty_right(const Board& board, PieceType player);

int selectColtoMove (const Board& board);

int aiMove(const Board& board);



#endif /* AI_H__ */
