#include "ai.h"
#include "board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


//If there is a winning move, take it.

//If your opponent has a winning move, take the move so he can’t take it.
bool threeInCol(const Board& board, int colIndex, PieceType player){
    
    for (int row = 0; row < NUM_ROWS - 4; row++){
        
        if (board.at(row,colIndex) == player &&
            board.at(row + 1, colIndex) == player &&
            board.at(row + 2, colIndex) == player &&
            board.at(row + 3, colIndex) == Empty){
            
            return true;
        }
    }
    
    return false;
}

//Returns true if a chip can be placed
bool checkForChipBelowEmpty(const Board& board, int col, int row){
    
    if (row == 0){
        return true;
    }
    
    else if (board.at(row - 1, col) != Empty){
        return true;
    }
    
    return false;
}


// XXX-
// XX-X
// X-XX
// -XXX
int threeInRowRightEmpty(const Board& board, int rowIndex, PieceType player){
    
    for (int col = 0; col < NUM_COLS - 3; col++){
        if (board.at(rowIndex,col) == player &&
            board.at(rowIndex,col + 1) == player &&
            board.at(rowIndex,col + 2) == player &&
            board.at(rowIndex,col + 3) == Empty){
            
            if (checkForChipBelowEmpty(board, col + 3, rowIndex)){
                return col + 3;
                break;
            }
        }
        
        else if (board.at(rowIndex,col) == player &&
            board.at(rowIndex,col + 1) == player &&
            board.at(rowIndex,col + 2) == Empty &&
            board.at(rowIndex,col + 3) == player){
            
            if (checkForChipBelowEmpty(board, col + 2, rowIndex)){
                return col + 2;
                break;
            }
        }
        
        else if (board.at(rowIndex,col) == player &&
                 board.at(rowIndex,col+ 1) == Empty &&
                 board.at(rowIndex,col+ 2) == player &&
                 board.at(rowIndex,col+ 3) == player){
            
            if (checkForChipBelowEmpty(board, col + 1, rowIndex)){
                return col + 1;
                break;
            }
        }
        
        else if (board.at(rowIndex,col) == Empty &&
                 board.at(rowIndex,col + 1) == player &&
                 board.at(rowIndex,col + 2) == player &&
                 board.at(rowIndex,col + 3) == player){
            
            if (checkForChipBelowEmpty(board, col, rowIndex)){
                return col;
                break;
            }
        }
    }
    
    //returns outside of range to use logic
    return NUM_COLS;
}




//--XX--
int deathMark_a(const Board& board, PieceType player){
    
    for (int row = 0; row < NUM_ROWS; row++){
        for (int col = 0; col < NUM_COLS - 5 ; col++){
            if (board.at(row,col) == Empty &&
                checkForChipBelowEmpty(board, col, row) &&
                
                board.at(row,col + 1) == Empty &&
                checkForChipBelowEmpty(board, col + 1, row) &&
                
                board.at(row,col + 2) == player &&
                checkForChipBelowEmpty(board, col + 2, row) &&
                
                board.at(row,col + 3) == player &&
                checkForChipBelowEmpty(board, col + 3, row) &&
                
                board.at(row,col + 4) == Empty &&
                checkForChipBelowEmpty(board, col + 4, row) &&
                
                board.at(row,col + 5) == Empty &&
                checkForChipBelowEmpty(board, col + 5, row)){
        
                return col + 4;
                break;
        
            }
        }
        
    }
    return NUM_COLS;
}





//-X-X-
int deathMark_b(const Board& board, PieceType player){
    
    for (int row = 0; row < NUM_ROWS; row++){
        for (int col = 0; col < NUM_COLS - 4; col++){
            if (board.at(row,col) == Empty &&
                checkForChipBelowEmpty(board, col, row) &&
                
                board.at(row,col + 1) == player &&
                checkForChipBelowEmpty(board, col + 1, row) &&
                
                board.at(row,col + 2) == Empty &&
                checkForChipBelowEmpty(board, col + 2, row) &&
                
                board.at(row,col + 3) == player &&
                checkForChipBelowEmpty(board, col + 3, row) &&
                
                board.at(row,col + 4) == Empty &&
                checkForChipBelowEmpty(board, col + 4, row)) {
                
                return col + 2;
                break;
            }
        }
        
    }
    return NUM_COLS;
}

int threeInRowRightAngleEmpty_right(const Board& board, PieceType player){
    
    for (int col = 0; col < NUM_COLS - 3; col++){
        for (int row = NUM_ROWS - 3; row < NUM_ROWS; row++){
            
            // X
            // SX
            // SSX
            // SSS-
            
            if (board.at(row,col) == player &&
                
                board.at(row - 1, col + 1) == player &&
                
                board.at(row - 2, col + 2) == player &&
                
                board.at(row - 3, col + 3) == Empty &&
                checkForChipBelowEmpty(board, col + 3, row - 3)){
                
                return col + 3;
                break;
            }
            
            // -
            // SX
            // SSX
            // SSSX
            
            else if (board.at(row,col) == Empty &&
                     checkForChipBelowEmpty(board, col, row) &&
                     
                     board.at(row - 1, col + 1) == player &&
                     
                     board.at(row - 2, col + 2) == player &&
                     
                     board.at(row - 3, col + 3) == player){
                
                return col;
                break;
                
            }
            
            // X
            // SX
            // SS-
            // SSSX
            
            else if (board.at(row,col) == player &&
                     
                     board.at(row - 1, col + 1) == player &&
                     
                     board.at(row - 2, col + 2) == Empty &&
                     checkForChipBelowEmpty(board, col + 2, row - 2) &&
                     
                     board.at(row - 3, col + 3) == player){
                
                return col + 2;
                break;
            }
            
            // X
            // S-
            // SSX
            // SSSX
            
            else if (board.at(row,col) == player &&
                     
                     board.at(row - 1, col + 1) == Empty &&
                     checkForChipBelowEmpty(board, col+1, row-1) &&
                     
                     board.at(row - 2, col + 2) == player &&
                     
                     board.at(row - 3, col + 3) == player){
                
                return col + 1;
                break;
                
            }
        }
    }
    
    return NUM_COLS;
}


int threeInRowRightAngleEmpty_left(const Board& board, PieceType player){
    
    for (int col = 0; col < NUM_COLS - 3; col++){
        for (int row = 0; row < NUM_ROWS - 3; row++){
            
            //    -
            //   X
            //  X
            // X
            
            if (board.at(row,col) == player &&
                
                board.at(row + 1,col + 1) == player &&
                
                board.at(row + 2, col + 2) == player &&
                
                board.at(row + 3, col + 3) == Empty &&
                checkForChipBelowEmpty(board, col + 3, row + 3)){
                
                return col + 3;
                break;
                
            }
            
            //    X
            //   X
            //  X
            // -
            
            else if (board.at(row,col) == Empty &&
                     checkForChipBelowEmpty(board, col, row) &&
                
                     board.at(row + 1, col + 1) == player &&
                
                     board.at(row + 2, col + 2) == player &&
                
                     board.at(row + 3, col + 3) == player){
                
                        return col;
                        break;
                
                    }
            
            //    X
            //   X
            //  -
            // X
            
            else if (board.at(row,col) == player &&
                     
                     
                     board.at(row + 1, col + 1) == Empty &&
                     checkForChipBelowEmpty(board, col + 1, row + 1) &&
                     
                     board.at(row + 2, col + 2) == player &&
                     
                     board.at(row + 3, col + 3) == player){
                
                        return col + 1;
                        break;
                
                    }
            
            //    X
            //   -
            //  X
            // X
            
            else if (board.at(row,col) == player &&
                     
                     
                     board.at(row + 1, col + 1) == player &&
                     
                     board.at(row + 2, col + 2) == Empty &&
                     checkForChipBelowEmpty(board, col + 2, row + 2) &&
                     
                     board.at(row + 3, col + 3) == player){
                
                return col + 2;
                break;
                
            }
        }
    }
    
    return NUM_COLS;
}


int findEmptyCol(const Board& board){
    
    for (int col = 0; col < NUM_COLS; col++){
        if (!board.isColFull(col)){
            return col;
        }
    }
    
    return rand() % NUM_ROWS;
}

int twoInRowRightAngleEmpty_left(const Board& board, PieceType player){
    
    for (int col = 0; col < NUM_COLS - 3; col++){
        for (int row = 0; row < NUM_ROWS - 3; row++){
            
            //    X
            //   -
            //  -
            // X
            
            if (board.at(row, col) == player &&
                
                board.at(row + 1, col + 1) == Empty &&
                checkForChipBelowEmpty(board, col + 1, row + 1) &&
                
                board.at(row + 2, col + 2) == Empty &&
                checkForChipBelowEmpty(board, col, row) &&
                
                board.at(row + 3, col + 3) == player){
                
                
                //    X
                //   -
                //  -X
                // X X
                
                
                if (board.at(row, col + 3) == player &&
                    checkForChipBelowEmpty(board, col + 3, row) &&
                    
                    board.at(row + 2, col + 3) == player &&
                    checkForChipBelowEmpty(board, col + 3, row + 2)){
                
                
                    return col + 3;
                    break;
                }
                
                return col + 2;
                break;
            }
        }
    }
    
    return NUM_COLS;
}

int twoInRowRightAngleEmpty_right(const Board& board, PieceType player){
    
    for (int col = 0; col < NUM_COLS - 3; col++){
        for (int row = NUM_ROWS - 3; row < NUM_ROWS; row++){
            
            // X
            //  -
            //   -
            //    X
            
            if (board.at(row,col) == player &&
                     
                board.at(row - 1, col + 1) == Empty &&
                checkForChipBelowEmpty(board, col + 1, row - 1) &&
                     
                board.at(row - 2, col + 2) == Empty &&
                checkForChipBelowEmpty(board, col + 2, row - 2) &&
                     
                board.at(row - 3, col + 3) == player){
                
                // X
                //  -
                //  X-
                //  X X
                if (board.at(row - 2, col + 1) == player &&
                    checkForChipBelowEmpty(board, col + 1, row - 2) &&
                    
                    board.at(row - 3, col + 2) == player &&
                    checkForChipBelowEmpty(board, col + 2, row - 3)){
                
                        return col + 1;
                        break;
                }
                
                return col + 2;
                break;
            }
        }
    }
    
    return NUM_COLS;
}



//Take the center square over edges and corners.
int selectColtoMove (const Board& board){
    
    if (!board.isColFull(3)){
        return 3;
    }
    
    else if (board.at(0,0) == 0){
        
        return 0;
    }
        
    else if (board.at(0,6) == 0){
        
        return 6;
    }
    
    else {
        
        return findEmptyCol(board);
    }
    
    //Take corner squares over edges.
    //Take edges if they are the only thing available.
    
}

int aiMove(const Board& board){
    
    //If your opponent has a winning move, take the move so he can’t take it.
    //If there is a winning move, take it.
    //Marks top of 3 to either block a win or win
    
    for (int col = 0; col < NUM_COLS; col++){
        
        //Defensive
        if (threeInCol(board, col, Player1)){
            
            return col;
            break;
        }
        
        //Attack
        else if (threeInCol(board, col, Player2)){

            return col;
            break;
        }
    }
    
    //If there is a winning move, take it.
    
    for (int row = 0; row < NUM_ROWS; row++){
        
        //Defense
        int move = threeInRowRightEmpty(board, row, Player1);
        if (move < NUM_COLS){
            
            return move;
            break;
        }
        
        //Attack
        move = threeInRowRightEmpty(board, row, Player2);
        if (move < NUM_COLS){
            
            return move;
            break;
        }
    }
    
    
    int moveAngle = threeInRowRightAngleEmpty_left(board,Player1);
    
    if (moveAngle < NUM_COLS){
        
        return moveAngle;
    }
    
    moveAngle = threeInRowRightAngleEmpty_right(board,Player1);
    
    if (moveAngle < NUM_COLS){
        
        return moveAngle;
    }
    
    moveAngle = threeInRowRightAngleEmpty_left(board,Player2);
    
    if (moveAngle < NUM_COLS){
        return moveAngle;
    }
    
    moveAngle = threeInRowRightAngleEmpty_right(board,Player2);
    
    if (moveAngle < NUM_COLS){
    
        return moveAngle;
    }
    
    //deathmark1strow
    int move = deathMark_a(board, Player1);
    
    if (move < NUM_COLS){
        
        return move;
    }
    
    move = deathMark_a(board, Player2);
    if (move < NUM_COLS){
        return move;
    }
    
    move = deathMark_b(board, Player1);
    
    if (move < NUM_COLS){
        
        return move;
    }
    
    move = deathMark_b(board, Player2);
    if (move < NUM_COLS){
        return move;
    }
    
    
    move = twoInRowRightAngleEmpty_left(board,Player1);
    if (move < NUM_COLS){
        return move;
    }
    
    move = twoInRowRightAngleEmpty_left(board,Player2);
    if (move < NUM_COLS){
        return move;
    }
    
   
    move = twoInRowRightAngleEmpty_right(board,Player1);
    if (move < NUM_COLS){
        return move;
    }
    
    move = twoInRowRightAngleEmpty_right(board,Player2);
    if (move < NUM_COLS){
        return move;
    }
    
    move = selectColtoMove(board);
    return move;
}


int connect4AI(const Board& board){
    
    //returning coulmn where chip is to be placed
    return aiMove(board);
}




