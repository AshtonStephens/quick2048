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

#define SIDE_BLOCK -1

class Board {
public:

    Board(int x, int y, int pwr) : 
        height_(x), width_(y), power_(pwr), board_(NULL) {
            reset_board();
            set_power(pwr);};

    ~Board();

    bool move_up   ();
    bool move_down ();
    bool move_left ();
    bool move_right();

    bool addRandom (); 
    void reset_board();
    void set_power(int pwr);
    friend std::ostream & operator << 
        (std::ostream &o, const Board& brd);
private:
    int  count_empty();
    void reset_locks();
    struct block {
        block() : power_(2), value_(0), lock_(false) {};
        const int operator = (int assign);
        const int operator = (const block &b);
        bool moveto (block &blk, bool &moved, int &score_);
        int power_;
        int value_;
        int lock_ ;
        friend std::ostream & operator <<
           (std::ostream &o, const block& blk);
    };
    friend std::ostream & operator <<
           (std::ostream &o, const block& blk);
    int height_, width_, power_, score_;
    block **board_; 
};

#endif

