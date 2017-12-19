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
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

/* -------------------------------------------------- *
 * BOARD
 * -------------------------------------------------- */

#define MAX_POWERS 2

Board::~Board()
{
    for (int i = 0; i < width_+2; ++i)
        delete [] board_[i];
    delete [] board_;
}

bool Board::move_up   ()
{
    // wid hei
    int row;
    bool moved = false;
    reset_locks();
    for (int col  = 0; col  < width_ ; ++col)
    for (int wave = 0; wave < height_; ++wave) {
        row = wave;
        while (board_[col+1][row+1].moveto(board_[col+1][row],moved)) {
            --row;
        } 
    }
    return moved;
}

bool Board::move_down ()
{
    int row;
    bool moved = false;
    reset_locks();
    for (int col  = 0; col < width_; ++col)
    for (int wave = height_-1; wave >= 0; --wave) {
        row = wave;
        while (board_[col+1][row+1].moveto(board_[col+1][row+2],moved)) {
            ++row;
        } 
    }
    return moved;
}

bool Board::move_left ()
{
    int  col;
    bool moved = false;
    reset_locks();
    for (int row  = 0; row  < height_; ++row)
    for (int wave = 0; wave < width_; ++wave) {
        col = wave;
        while (board_[col+1][row+1].moveto(board_[col][row+1],moved)) {
            --col;
        } 
    }
    return moved;
}

bool Board::move_right()
{
    int  col;
    bool moved = false;
    reset_locks();
    for (int row  = 0; row < height_; ++row)
    for (int wave = width_-1; wave >= 0; wave--) {
        col = wave;
        while (board_[col+1][row+1].moveto(board_[col+2][row+1],moved)) {
            ++col;
        } 
    }
    return moved;
}

void Board::reset_locks()
{
    for (int j = 0; j < height_; ++j) 
        for (int i = 0; i < width_; ++i)
            board_[i+1][j+1].lock_ = false;
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
    //std::cout << "ERROR NOT IMPEMENTED ADD RANDOM\n" << std::endl;
    
    int num_empty = count_empty();
    int rand_choice, col, row;

    if (num_empty == 0) {
       return false; 
    } else {
        rand_choice = rand() % num_empty;
        
      //  std::cerr << "rand_choice = " << rand_choice << std::endl;

        for (col = 0; col < width_; ++col)
            for (row = 0; row < height_; ++row)
                if (board_[col+1][row+1].value_ == 0)
                if (rand_choice-- == 0) 
                    board_[col+1][row+1] = rand() % MAX_POWERS + 1; 
       // std::cout << *this;
        return true; 
    }
}

int Board::count_empty() 
{
    int num_free = 0;
    for (int col = 0; col < width_; ++col)
        for (int row = 0; row < height_; ++row)
            if (board_[col+1][row+1].value_ == 0) ++num_free; 
    return num_free;
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
    
void Board::set_power(int pwr)
{
    power_ = pwr;
    for (int i = 0; i < width_; ++i) {
        for (int j = 0; j < height_; ++j) {
            board_[i+1][j+1].power_ = pwr;
        }
    }
    return;
}

/* -------------------------------------------------- *
 * BLOCK 
 * -------------------------------------------------- */

const int Board::block::operator = (int assign)
{
    lock_ = false;
    return value_ = assign;
}

bool Board::block::moveto (block &blk, bool &moved)
{
    if (value_ == 0 || blk.lock_ ||
        blk.value_ == SIDE_BLOCK) {
        return false;
    } else if (blk.value_ == 0) {
        blk.value_  = value_;
        value_      = 0;
        moved       = true;
        return true;
    } else if (blk.value_ == value_) {
        blk.lock_   = true;
        blk.value_ += 1;
        value_      = 0;
        moved       = true;
        return false;
    }
    return false;
}

int pads(int num) 
{
    int i = 0;
    if (num < 0) {
        num = -num;
        ++i;
    } else if (num == 0) return 1;
    for (i; num != 0; i++)
       num /= 10; 
    return i;
}

std::ostream & operator <<
(std::ostream &o, const Board::block& blk)
{
    (void) o;
    (void) blk;
    int pwr = 1;
    int padding, i;

    for (i = 0; i < blk.value_; ++i)
       pwr *= blk.power_;
    
    padding = pads(pwr); 
       
    if (blk.value_ == 0) {
        o << "\033[40;7;10m" << "--X--" << "\033[0m";
    } else {
        o << "\033["<< (blk.value_%6 + 31) << ";7";
        if (((blk.value_)/7 )%2 == 1) o << ";2";
        if (((blk.value_)/14)%2 == 1) o << ";1";
        o << "m";
        for (i = 0; i < 5-padding; ++i) o << " ";
        o << pwr << "\033[40;0m";
    } 
    return o;
}











