/* 
 * game.h 
 *
 * holds the game board and information and displays in a
 * nice way.
 *
 * By: AshtonStephens
 * Date: 12/20/17
 *
 */

#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "score.h"
#include <vector>
#include <string>
#include "score.h"

class Game {
public:
    Game (int w, int h, int pow) : gb_(w,h,pow), first_(true) 
    {set_power(pow);};

    ~Game();
    friend std::ostream & operator << (std::ostream &o,  Game& g);
    Board gb_;  
    bool addRandom();

    bool move_up   ();
    bool move_down ();
    bool move_right();
    bool move_left ();
    void set_power (int power);
    bool over ();
private:
    std::string divider(char corner, char line);
    bool winning;
    int  power_;
    bool first_;
    int  myscore_;
    Score my_score_;
    Score high_score_;
};

#endif
