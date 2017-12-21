

#include "game.h"

template <int N>
int chooseRandom(const int (&t)[N])
{ return t[rand() % N]; }
const int probs[] = {1,1,1,1,1,1,1,1,1,2};

Game::~Game()
{
    return;
}

bool Game::move_up   ()
{gb_.move_up(my_score_);}

bool Game::move_down ()
{gb_.move_down(my_score_);}

bool Game::move_right ()
{gb_.move_right(my_score_);}

bool Game::move_left ()
{gb_.move_left(my_score_);}

void Game::set_power (int power)
{
    power_ = power;
    my_score_.set_power(power);
    high_score_.set_power(power);
    gb_.set_power(power);
}

bool Game::addRandom()
{
    int num_empty_ = gb_.num_empty();
    int rand_choice;
    if (num_empty_ == 0) {
       return false; 
    } else {
        rand_choice = rand() % num_empty_;
        Board::block &b = gb_.nth_empty(rand_choice);
        b = chooseRandom(probs);
        return true; 
    }

}

bool Game::over ()
{
    Board gb;
    Score s;
    if (gb_.num_empty() == 0) {
        gb = gb_;
        if ( !gb.move_up(s) && !gb.move_left(s)) {
            return true;
        }
    }  
    return false;
}

std::string Game::divider(char corner, char line)
{
    std::string div = "";
    int game_width = gb_.width_ * gb_.block_width_;
    div += corner;
    for (int i = 0; i < game_width; ++i) div += line;
    div += corner;
    return div;
}

std::ostream & operator << 
(std::ostream &o, Game& g)
{   
    // o << "\033["<< g.gb_.height_ + 2 << "B";
    int numclear = g.gb_.height_ + 3;
    for (int i = 0; i < numclear; ++i) {
        o << "\033[1A\033[K";
    }
    
    o << g.divider('x','-') << std::endl; 
    o << g.gb_;
    o << g.divider('x','-') << std::endl; 
    o << "SCORE: " << g.my_score_.get_value() << std::endl;
   return o;
}


