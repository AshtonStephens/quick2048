/* 
 * board.h
 *
 * headerfile for the board data abstraction 
 * for implementing 2048 game.
 *
 * By: Ashton Stephens
 * Date: 12/18/17
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include "score.h"

#define EDGE  -1

static const int DEFAULT_POWER  = 2;
static const int DEFAULT_VALUE = 0;
static const int DEFAULT_MIN_BLOCK_WIDTH = 5;


class Board {
public:
    class block;


    Board () : 
        width_(0), height_(0), board_(NULL), 
        power_(DEFAULT_POWER),
        block_width_    (DEFAULT_MIN_BLOCK_WIDTH),
        min_block_width_(DEFAULT_MIN_BLOCK_WIDTH),
        highest_value_  (DEFAULT_VALUE) {};

    Board (const Board &b);
    Board (int w, int h, int pwr);
    ~Board();
    
    // TODO: REMOVE
    bool addRandom();
    // TODO: REMOVE

    const Board &operator  = (const Board &b);
    const Board &operator += (const Board &b);
    
    // returns if something moved
    bool move_up   (Score &score);
    bool move_down (Score &score);
    bool move_left (Score &score);
    bool move_right(Score &score);
    
    void set_power  (int  pwr);
    void set_value  (int  value);
    void set_lock   (bool lock);
    void set_block_width(int  block_width);
    
    int   num_empty();
    void  ensure_fitting() ;
    block &nth_empty (int n);

    struct board_attributes {
        int power_          ;
        int block_width_    ;
        int min_block_width_;   
    };

    class  block {
        public:
        block() : attr(NULL), power_(DEFAULT_POWER), 
        value_(DEFAULT_VALUE), new_(false), lock_(false), highlight_(0) {};
        const block& operator = (int assign);
        const block& operator = (const block &b);
        const block& operator+= (const block &b);
        const bool   operator!= (const int value);
        bool moveto (block &blk, bool &moved, Score &s, Board& brd);
        friend std::ostream & operator << (std::ostream &o, const block& blk);
        Board::board_attributes *attr;
        int  power_;
        int  value_;
        bool new_  ;
        bool lock_ ;
        int  block_width_;
        int  highlight_;
    };
    
    friend std::ostream & operator << (std::ostream &o, const Board& brd);
    friend std::ostream & operator << (std::ostream &o, const block& blk);
    friend bool block::moveto (block &blk, bool &moved, Score &s, Board &brd);
    int     concat (block **dest, block **src, int w, int h);
    block** allocate_board   (int w, int h);
    block** deallocate_board (block** brd, int w);
    void    initialize_edges (block** brd, int w, int h);

    int width_  ;
    int height_ ;
    block **board_;
    
    int power_  ;
    int block_width_;
    int min_block_width_;
};

#endif

