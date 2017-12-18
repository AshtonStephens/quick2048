/* 
 * board.h
 *
 * headerfile for the board data abstraction for implementing
 * 2048 game board. 
 *
 * By: Ashton Stephens
 * Date: 12/18/17
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

class Board {
public:

    Board(int x, int y, int val);
    ~Board();

    bool move_up   ();
    bool move_down ();
    bool move_left ();
    bool move_right();

    friend std::ostream & operator << 
        (std::ostream &o, const Board& brd);
private:
    struct block {
        block();
        ~block();
        const int operator = (int assign);
        bool moveto (block &blk);
        friend std::ostream & operator <<
           (std::ostream &o, const block& blk);

        int value_;
        int lock_ ;
    };
    block *board_; 
}


#endif
