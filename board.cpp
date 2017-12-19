/* 
 * board.cpp
 *
 * implementation for the board data abstraction 
 * for implementing 2048 game.
 *
 * By: Ashton Stephens
 * Date: 12/18/17
 *
 */

#include <time.h>
#include "board.h"

/* -------------------------------------------------- *
 * BOARD
 * -------------------------------------------------- */

Board::~Board()
{
}

bool Board::move_up   ()
{

    return false;
}

bool Board::move_down ()
{
    return false;
}

bool Board::move_left ()
{
    return false;
}

bool Board::move_right()
{
    std::cout << "ERROR NOT IMPEMENTED MOVE RIGHT\n" << std::endl;
    return true;
}

std::ostream & operator << 
(std::ostream &o, const Board& brd)
{
    for (int j = 0; j < brd.height_; ++j) {
        for (int i = 0; i < brd.width_; ++i) 
            o << brd.board_[i+1][j+1];
        o << std::endl;
    }
    return o;
}

bool Board::addRandom ()
{
    std::cout << "ERROR NOT IMPEMENTED ADD RANDOM\n" << std::endl;
    return true;
}
    
void Board::reset_board()
{
    int height = height_ + 2;
    int width  = width_  + 2;

    if (board_ == NULL) {
        board_ = new block* [width]; 
        for (int i = 0; i < width; ++i)
            board_[i] = new block[height]; 
    }
    
    for (int i = 0; i < width ; ++i) board_[i][0]        = SIDE_BLOCK;
    for (int i = 0; i < width ; ++i) board_[i][height-1] = SIDE_BLOCK;
    for (int i = 0; i < height; ++i) board_[0][i]        = SIDE_BLOCK;
    for (int i = 0; i < height; ++i) board_[width-1][i]  = SIDE_BLOCK;
}
    
void Board::set_value(int val)
{
    value_ = val;
    for (int i; i < width_; ++i) {
        for (int j; j < height_; ++j) {
            board_[i+1][j+1].value_ = val;
        }
    }
    return;
}

/* -------------------------------------------------- *
 * BLOCK 
 * -------------------------------------------------- */

const int Board::block::operator = (int assign)
{
    (void) assign;
    return 1;
}

bool      Board::block::moveto (block &blk)
{
    (void) blk;
    return true;
}

std::ostream & operator <<
(std::ostream &o, const Board::block& blk)
{
    (void) o;
    (void) blk;
    int pwr = 1;
    
    for (int i = 0; i < blk.value_; ++i)
       pwr *= blk.power_;
    
    if (blk.value_ == 0) {
        o << "\033[40;10m" << 'X' << "\033[40;0m";
    } else {
        o << "\033["<< (blk.value_ + 30) << ";"<< (((10+blk.value_)/10)%2)*9+1
          <<"m" << pwr << "\033[40;0m";
    } 
    return o;
}





