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

#include "board.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

/* -------------------------------------------------- *
 * BOARD
 * -------------------------------------------------- */

#define DBGP std::cerr << \
    "debug(" << __func__ << \
    "["<<__LINE__<< "])" << \
    std::endl << *this << std::endl

int deci_leng(int num);
int power_op (const int val, const int pow);
Board::Board (int w, int h, int pwr)
{
    width_  = w;
    height_ = h;
    board_  = allocate_board (w,h);
    initialize_edges(board_,w,h);
    min_block_width_ = 5;
    set_block_width(5);
    set_value  (0); 
    set_lock   (false);
    set_power  (pwr);
}

// ALLOCATE
Board::block** Board::allocate_board  (int w, int h)
{
    w+=2;h+=2;
    Board::block **new_board = new Board::block*[w]; 
    for (int i = 0; i < w; ++i) {
        new_board[i] = new block[h];
    } 
    return new_board;
}


Board::Board (const Board &b) 
{
    //board_ = NULL;
    *this  = b;
}

const Board &Board::operator  = (const Board &b)
{
    board_  = deallocate_board (board_, width_);
    board_  = allocate_board   (b.width_, b.height_);
    initialize_edges (board_,b.width_,b.height_);
    width_  = b.width_;
    height_ = b.height_;
    
    concat (board_, b.board_, width_, height_);
    
    set_block_width(b.block_width_);
    set_power  (b.power_);
    set_lock   (false);
    return *this += b;
}

const Board &Board::operator += (const Board &b)
{
    int width  = width_;
    int height = height_;
    if   (b.width_  < width ) width  = b.width_ ; 
    if   (b.height_ < height) height = b.height_; 
    concat(board_,b.board_,width,height);
    return *this; 
}

Board::~Board()
{
    if (board_ == NULL) return;
    for (int i = 0; i < width_+2; ++i)
        delete [] board_[i];
    delete [] board_;
}

int Board::num_empty()
{
    int num_free = 0;
    for (int col = 0; col < width_; ++col)
        for (int row = 0; row < height_; ++row)
            if (board_[col+1][row+1].value_ == 0) ++num_free; 
    return num_free;
}
 
/* -------------------------------------------------- *
 * BLOCK 
 * -------------------------------------------------- */

const Board::block& Board::block::operator = (const Board::block &b)
{
    power_ = b.power_;
    value_ = b.value_;
    lock_  = b.lock_;
    return *this;
}

const Board::block& Board::block::operator += (const block &b)
{
    value_ += b.value_;
    return *this;
}

const Board::block& Board::block::operator = (const int assign)
{
    value_ = assign;
    return *this;
}
const bool   Board::block::operator!= (const int value)
{
    return value == value_;
}

void Board::ensure_fitting() 
{
    int wid = std::to_string(power_op(highest_value_,power_)).length() + 2;
    if (wid > min_block_width_) {
        set_block_width(wid);
    } else {
        set_block_width(min_block_width_);
    }
}

bool Board::block::moveto (block &blk, 
        bool &moved, Score &score, Board& brd)
{
    int wid;
    if (value_ == 0 || blk.lock_ ||
        blk.value_ == EDGE) {
        // doing nothing to the block
        return false;
    } else if (blk.value_ == 0) {
        // moving a block over
        blk.value_  = value_;
        value_      = 0;
        moved       = true;
        return true;
    } else if (blk.value_ == value_) {
        // Combining two blocks
        blk.lock_   = true;
        blk.value_ += 1;
        score += blk.value_;
        if (blk.value_ > brd.highest_value_) {
            brd.highest_value_ = blk.value_;
            brd.ensure_fitting();
        }
        value_      = 0;
        moved       = true;
        return false;
    }
    return false;
}



/* * * * * *
 *  Small helper functions
 * * * * * */

// returns the number of characters required to 
// print the integer in decimal
int deci_leng(int num) 
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

// returns val to the power of pow
int power_op (const int val, const int pow)
{
    int ret = 1;
    for (int i = 0; i < val; ++i)
        ret *= pow;
    return ret; 
}

// SETTING ALL THE BLOCK VALUE FUINCTIONS

void Board::set_power  (int  pwr)
{
    power_ = pwr;
    ensure_fitting();
    for (int j = 0; j < height_; ++j) 
        for (int i = 0; i < width_; ++i)
            board_[i+1][j+1].power_ = pwr;
}

void Board::set_value  (int  value)
{
    highest_value_ = value;
    for (int j = 0; j < height_; ++j) 
        for (int i = 0; i < width_; ++i)
            board_[i+1][j+1].value_ = value;
}

void Board::set_lock   (bool lock)
{
    for (int j = 0; j < height_; ++j) 
        for (int i = 0; i < width_; ++i)
            board_[i+1][j+1].lock_ = lock;
}

void Board::set_block_width(int  block_width)
{
    block_width_ = block_width;
    for (int j = 0; j < height_; ++j) 
        for (int i = 0; i < width_; ++i)
            board_[i+1][j+1].block_width_ = block_width;
}

//// MOVEMENT FUNCTIONS

bool Board::move_down (Score &score)
{
    int row;
    bool moved = false;
    set_lock(false);
    for (int col  = 0; col  < width_ ; ++col)
    for (int wave = 0; wave < height_; ++wave) {
        row = wave;
        while (board_[col+1][row+1].moveto(board_[col+1][row],moved,score,*this)) {
            --row;
        } 
    }
    return moved;
}

bool Board::move_up   (Score &score)
{
    int row;
    bool moved = false;
    set_lock(false);
    for (int col  = 0; col < width_; ++col)
    for (int wave = height_-1; wave >= 0; --wave) {
        row = wave;
        while (board_[col+1][row+1].moveto(board_[col+1][row+2],moved,score,*this)) {
            ++row;
        } 
    }
    return moved;
}

bool Board::move_left (Score &score)
{
    int  col;
    bool moved = false;
    set_lock(false);
    for (int row  = 0; row  < height_; ++row)
    for (int wave = 0; wave < width_; ++wave) {
        col = wave;
        while (board_[col+1][row+1].moveto(board_[col][row+1],moved,score,*this)) {
            --col;
        } 
    }
    return moved;
}

bool Board::move_right (Score &score)
{
    int  col;
    bool moved = false;
    set_lock(false);
    for (int row  = 0; row < height_; ++row)
    for (int wave = width_-1; wave >= 0; wave--) {
        col = wave;
        while (board_[col+1][row+1].moveto(board_[col+2][row+1],moved,score,*this)) {
            ++col;
        } 
    }
    return moved;
}


Board::block& Board::nth_empty (int n)
{
    for (int col = 0; col < width_; ++col)
        for (int row = 0; row < height_; ++row)
            if (board_[col+1][row+1].value_ == 0)
                if (n-- == 0) return board_[col+1][row+1];
                    
}

int Board::concat (Board::block **dest, Board::block **src, int w, int h)
{
    for (int c = 0; c < w; ++c) {
        for (int r = 0; r < h; ++r) {
            dest[c+1][r+1] += src[c+1][r+1]; 
        }
    } 
}

void Board::initialize_edges(Board::block** brd, int w, int h) 
{
    w+=2; h+=2;
    for (int i = 0; i < w; ++i) brd[i][0]   = EDGE;
    for (int i = 0; i < w; ++i) brd[i][h-1] = EDGE;
    for (int i = 0; i < h; ++i) brd[0][i]   = EDGE;
    for (int i = 0; i < h; ++i) brd[w-1][i] = EDGE;
}

Board::block** Board::deallocate_board (Board::block** brd, int w)
{
    if (brd == NULL) return NULL;
    for (int i = 0; i < w; ++i) {
        delete [] brd[i];
    }
    delete [] brd;
    return NULL;
}

/*
Board::block** Board::delete_board(Board::block **board, int width)
{
    for (int i = 0; i < width+2; ++i)
        delete [] board[i];
    delete [] board;
    return NULL;
} 

Board::block** Board::new_board(int width, int height)
{   
    Board::block **new_board; 
    height += 2;
    width  += 2;

    new_board = new block*[width]; 
    for (int i = 0; i < width; ++i)
        new_board[i] = new block[height]; 
    
    for (int i = 0; i < width ; ++i) new_board[i][0]        = EDGE;
    for (int i = 0; i < width ; ++i) new_board[i][height-1] = EDGE;
    for (int i = 0; i < height; ++i) new_board[0][i]        = EDGE;
    for (int i = 0; i < height; ++i) new_board[width-1][i]  = EDGE;
    
    return new_board;
}
    
Board::block** Board::new_board_copy (Board::block **board, int width, int height)
{
    Board::block** new_board_ = new_board(width, height);
    for (int col = 0; 
            board_[col+1][0].value_ != EDGE &&
            new_board_[col+1][0].value_ != EDGE;
            ++col) {
        for (int row = 0;
                board_    [col+1][row+1].value_ != EDGE &&
                new_board_[col+1][row+1].value_ != EDGE;
                ++row) {
                new_board_[col+1][row+1] = board_[col+1][row+1];
        }
    }
    board_ = new_board_;
    std::cerr << *this << std::endl;
    return new_board_;
}
*/

std::ostream & operator << 
(std::ostream &o, const Board& brd)
{
    for (int j = brd.height_-1; j >= 0; --j) {
        o << "|"; 
        for (int i = 0; i < brd.width_; ++i) {
            o << brd.board_[i+1][j+1];
        }
        o << "|" << std::endl;
    }
    return o;
}

std::string centered_string(const std::string &centered, int width, const char padding)
{
    std::string a = "";
    int padd,i,len = centered.length();
    padd  = (width - len) >> 1;
    padd += (width - len) &  1;
    for (i = 0; i < padd; ++i) {a += padding;}
    a += centered;
    padd -= (width - len) &  1;
    for (i = 0; i < padd; ++i) {a += padding;}
    return a; 
}

std::ostream & operator <<
(std::ostream &o, const Board::block& blk)
{
    int pwr   = power_op(blk.value_,blk.power_);
    std::string inner_val;

    if (blk.value_ == 0) {
        inner_val = "X";
        o << "\033[40;7;10m";
        o << centered_string(inner_val,blk.block_width_,'-');
        o << "\033[0m";
    } else {
        inner_val = std::to_string(pwr);
        o << "\033["<< ((blk.value_-1)%6 + 31) << ";7";
        if (((blk.value_)/7 )%2 == 1) o << ";2";
        if (((blk.value_)/14)%2 == 1) o << ";1";
        o << "m";
        o << centered_string(inner_val,blk.block_width_,' ');
        o << "\033[40;0m";
    } 
    return o;
}
