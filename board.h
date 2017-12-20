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

#define EDGE -1

class Board {
public:
    class block;


    Board () : width_(0), height_(0), board_(NULL)  {};
    Board (const Board &b);
    Board (int w, int h, int pwr);
    ~Board();
    
    // TODO: REMOVE
    bool addRandom();
    // TODO: REMOVE

    const Board &operator  = (const Board &b);
    const Board &operator += (const Board &b);
    
    // returns if something moved
    bool move_up   ();
    bool move_down ();
    bool move_left ();
    bool move_right();
    
    void set_power  (int  pwr);
    void set_value  (int  value);
    void set_lock   (bool lock);
    void set_padding(int  padding);
    
    int   num_empty();
    block &nth_empty (int n);

    class block {
        public:
        block() : power_(2), value_(0), lock_(false), 
        padding_(5), highlight_(0) {};
        const block& operator = (int assign);
        const block& operator = (const block &b);
        const block& operator+= (const block &b);
        const bool   operator!= (const int value);
        bool moveto (block &blk, bool &moved);
        friend std::ostream & operator << (std::ostream &o, const block& blk);
        int  power_;
        int  value_;
        bool lock_ ;
        int  padding_;
        int  highlight_;
    };
    
    friend std::ostream & operator << (std::ostream &o, const Board& brd);
    friend std::ostream & operator << (std::ostream &o, const block& blk);

private:

    void    concat (block **dest, block **src, int w, int h);
    block** allocate_board   (int w, int h);
    block** deallocate_board (block** brd, int w);
    void    initialize_edges (block** brd, int w, int h);

    int width_  ;
    int height_ ;
    int power_  ;
    int padding_;

    block **board_;
};

#endif

