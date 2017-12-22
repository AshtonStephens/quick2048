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
static const int DEFAULT_BLOCK_WIDTH = 5;


class Board {
public:
    class block;


    Board () : width_(0), height_(0), board_(NULL) {}

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
    int   num_filled();
    void  update_block_width() ;
    block &nth_empty (int n);

    struct board_attributes 
    {
        board_attributes(): power_(DEFAULT_POWER), 
        block_width_    (DEFAULT_BLOCK_WIDTH), 
        min_block_width_(DEFAULT_BLOCK_WIDTH),
        highest_value_  (DEFAULT_VALUE),
        update_block_width_(true),
        background_data_("47;30") {};
        int power_          ;
        int block_width_    ;
        int min_block_width_;   
        int highest_value_  ;
        bool update_block_width_;
        std::string background_data_;
    };

    class  block {
        public:
        block() : 
        attr_(NULL),
        value_(DEFAULT_VALUE), new_(false), lock_(false), highlight_(0) {};
        const block& assign_value(int assign);
        const block& operator =  (int assign);
        const block& operator =  (const block &b);
        const block& operator+=  (const block &b);
        const bool   operator!=  (const int value);
        bool moveto (block &blk, bool &moved, Score &s);

        void update_printstring();
        
        friend std::ostream & operator << (std::ostream &o, const block& blk);
        Board::board_attributes *attr_;

        int  value_ ;
        bool new_   ;
        bool lock_  ;
        int  highlight_;
    };
    
    friend std::ostream & operator << (std::ostream &o, Board& brd);
    friend std::ostream & operator << (std::ostream &o, const block& blk);
    int     concat (block **dest, block **src, int w, int h);
    block** allocate_board   (int w, int h);
    block** deallocate_board (block** brd, int w);
    void  initialize_edges (block** brd, int w, int h);

    int width_  ;
    int height_ ;
    block **board_; 
    board_attributes attr_; 
};

#endif

