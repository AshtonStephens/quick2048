/* 
 * game.h 
 *
 * holds the game board and information and displays in a
 * nice way.
 *
 * by: AshtonStephens
 * date: 12-20-17
 * edited : 3-23-19
 *
 * */

#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "score.h"
#include <vector>
#include <string>
#include "score.h"

class Game {
public:
    Game (int w, int h, int pow) : gb_(w,h,pow), first_(true),
        winning_(false) {set_power(pow);};
     
    const Game & operator= (const Game & g);
    ~Game();
    friend std::ostream & operator << (std::ostream &o,  Game& g);
    bool addRandom();

    bool move_up   ();
    bool move_down ();
    bool move_right();
    bool move_left ();
    void resize(int wid, int hei);
    void set_power (int power);
    bool over ();
    Board gb_;  
    Score my_score_;
    Score hi_score_;
private:
    std::string divider(char corner, char line);
    std::string score_line();
    void  update_highscore();
    int   power_;
    bool  first_;
    bool  winning_;
};

#endif
