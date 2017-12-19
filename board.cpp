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

/* -------------------------------------------------- *
 * BOARD
 * -------------------------------------------------- */

Board::Board(int x, int y, int val)
{
    (void) x;
    (void) y;
    (void) val;
}

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
    return false;
}

std::ostream & operator << 
(std::ostream &o, const Board& brd)
{
    (void) o;
    (void) brd;
    return  o << 100; 
}

/* -------------------------------------------------- *
 * BLOCK 
 * -------------------------------------------------- */

Board::block::block()
{
}

Board::block::~block()
{
}

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
}



