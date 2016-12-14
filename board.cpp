#include "board.h"

Board::Board() {
    for (int row = 0; row < NUM_ROWS; row++)
    {
        for (int col = 0; col < NUM_COLS; col++)
        {
            data[row][col] = Empty;
        }
    }
    nextPlayer_to_move = Player1;
}

Board::Board(const string &fen){
    int blank;
    int row = 0;
    int col = 0;
    char garbage = '/';
    int length = (int) fen.length();
    
    for (int i = 0; i < length - 2; i++) {
        
        if (fen[i] == PLAYER1_TOKEN) {
            data[row][col] = Player1;
            col++;
        }
        
        else if (fen[i] == PLAYER2_TOKEN) {
            data[row][col] = Player2;
            col++;
        }
        else if (fen[i] == garbage) {
            row++;
            col = 0;
        }
        else {
            blank = fen[i];
            int test = blank + col;
            for (int i = col; i < test; i++) {
                data[row][i] = Empty;
                col++;
            }
        }
        
    }
    
    if (fen[length-1] == PLAYER1_TOKEN){
        nextPlayer_to_move = Player1;
    }
    else {
        nextPlayer_to_move = Player2;
    }
    
}

void Board::printBoard_as_FENstring(ostream &os) const {
    int count = 0;
    char slash = '/';
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (data[i][j] == Empty) {
                count++;
            }
            else if (count != 0) {
                os << count;
                count = 0;
            }
            
            if (data[i][j] == Player1) {
                os << PLAYER1_TOKEN;
            }
            else if (data[i][j] == Player2) {
                os << PLAYER2_TOKEN;
            }
        }
        if (count != 0) {
            os << count;
            count = 0;
        }
        
        if (i < NUM_ROWS - 1) {
            os << slash;
        }
    }
    
    os << " ";
    if (nextPlayer_to_move == Player1) {
        os << PLAYER1_TOKEN;
    }
    else if (nextPlayer_to_move == Player2) {
        os << PLAYER2_TOKEN;
    }
    
    
}

PieceType Board::atLocation(int row, int col) {
    return data[row][col];
}

void Board::prettyPrintBoard(ostream &os) const {
    os << endl;
    for (int row = NUM_ROWS - 1; row >= 0; row--)  {
        os << "     +---+---+---+---+---+---+---+"
        << endl
        << "    ";
        
        for (int col = 0; col < NUM_COLS; col++)   {
            os << " | " ;
            if ( data[row][col] == Player1)
                os <<  PLAYER1_TOKEN;
            else if (data[row][col] == Player2)
                os << PLAYER2_TOKEN;
            else
                os << EMPTY_TOKEN;
        }
        os << " |" << endl;
    }
    os << "     +---+---+---+---+---+---+---+" << endl
    <<"  col  1   2   3   4   5   6   7" << endl;
    return;
}

int Board::toMove() const {
    if (nextPlayer_to_move == Player1)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

Result Board::makeMove(int col) {
    if (col < 0 || col > NUM_COLS) {
        return IllegalMove;
    }
    
    int freeRow = getFirstFreeRow(col);
    
    if (!inBounds(freeRow, col)) {
        return IllegalMove;
    }
    if (toMove() == 1) {
        data[freeRow][col] = Player1;
    }
    if (toMove() == 2) {
        data[freeRow][col] = Player2;
    }
    if (isWin(freeRow, col)) {
        return Win;
    }
    if (isBoardFull()) {
        return Draw;
    }
    updateToMove();
    return NoResult;
}

int Board::getFirstFreeRow(int col) const {
    for (int row = 0; row < NUM_ROWS; row++) {
        if (data[row][col] == Empty) {
            return row;
        }
    }
    return NUM_ROWS;
}

PieceType Board::updateToMove() {
    if (nextPlayer_to_move == Player1) {
        nextPlayer_to_move = Player2;
        return Player2;
    }
    else {
        nextPlayer_to_move = Player1;
        return Player1;
    }
}

bool Board::isBoardFull() const {
    for (int rows = 0; rows < NUM_ROWS; rows++) {
        for (int cols = 0; cols < NUM_COLS; cols++) {
            if (data[rows][cols] == Empty) {
                return false;
            }
        }
    }
    return true;
}

bool Board::inBounds(int row, int col) const {
    if (row < NUM_ROWS && col < NUM_COLS && row >= 0 && col >= 0) {
        return true;
    }
    return false;
}


int Board::piecesInDirection(int row, int col, int dRow, int dCol) const {
    int checkRow = row + dRow;
    int checkCol = col + dCol;
    int count = 0;
    
    PieceType pt = data[row][col];
    
    while (inBounds(checkRow, checkCol)) {
        if (data[checkRow][checkCol] == pt) {
            count++;
        }
        else {
            return count;
        }
        checkRow += dRow;
        checkCol += dCol;
    }
    
    return count;
}

bool Board::isWin(int row, int col) const {
    int numToWin = 3;
    
    if (piecesInDirection(row, col, -1, 0) == numToWin) {
        return true;
    }
    else if (piecesInDirection(row, col, 0, 1 ) +
             piecesInDirection(row, col, 0, -1)  >= numToWin) {
        return true;
    }
    
    else if (piecesInDirection(row, col, -1, -1) +
             piecesInDirection(row, col, 1, 1) >= numToWin) {
        return true;
    }
    else if (piecesInDirection(row, col, -1, 1) +
             piecesInDirection(row, col, 1, -1) >= numToWin) {
        return true;
    }
    
    return false;
    
}




//AI Functions

//Returns True if Col is Full
bool Board::isColFull(int col) const {
    for (int row = 0; row < NUM_ROWS; row++) {
        if (data[row][col] == Empty) {
            return false;
        }
    }
    return true;
}


//returns 1 for player 1, 2 for player 2, 0 for empty
PieceType Board::at(int row, int col) const {
    return data[row][col];
}






