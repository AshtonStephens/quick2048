/* 
 * game.cpp
 *
 * implementation of 2048 game to output board and update the game
 * with each movement.
 * 
 * by: Ashton Stephens
 * date: 12-20-17
 * documented: 3-23-19
 *
 * */

#include "game.h"

template <int N>
int chooseRandom(const int (&t)[N])
{ return t[rand() % N]; }

// allows for easy population of the probabilities
// of different powers populating the board on a move
const int probs[] = {1,1,1,1,1,1,1,1,1,2};

const Game & Game::operator= (const Game & g)
{
    winning_    = g.winning_;
    power_      = g.power_;
    gb_         = g.gb_;
    my_score_   = g.my_score_;
    hi_score_   = g.hi_score_;
}

Game::~Game()
{
    return;
}

bool Game::move_up   ()
{
    bool moved = gb_.move_up(my_score_);
    update_highscore();
    return moved;
}

bool Game::move_down ()
{
    bool moved = gb_.move_down(my_score_);
    update_highscore();
    return moved;
}

bool Game::move_right ()
{
    bool moved = gb_.move_right(my_score_);
    update_highscore();
    return moved;
}

bool Game::move_left ()
{
    bool moved = gb_.move_left(my_score_);
    update_highscore();
    return moved;
}

void Game::resize(int wid, int hei)
{
    Board temp (wid,hei,gb_.attr_.power_);
    temp += gb_;
    gb_   = temp;
}

void Game::set_power (int power)
{
    power_ = power;
    my_score_.set_power(power);
    hi_score_.set_power(power);
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

        // TODO: better method for checking if there's a zero
        if ( gb_.width_ == 0 || gb_.height_ == 0 ||
            !gb.move_up(s) && !gb.move_left(s)) {
            return true;
        }
    }  
    return false;
}

std::string Game::divider(char corner, char line)
{
    std::string div = "";
    int game_width = gb_.width_ * gb_.attr_.block_width_;
    div += corner;
    for (int i = 0; i < game_width; ++i) div += line;
    div += corner;
    return div;
}


void  Game::update_highscore()
{
    if (!winning_)  {
        if (my_score_.get_value() > hi_score_.get_value()) {
            winning_ = true;
        }
    }
}

std::string Game::score_line()
{
    static const std::string my_color = "\033[10;32m";
    static const std::string hi_color = "\033[10;31m";

    static const std::string my_sd = "SCORE: ";
    static const std::string hi_sd = "BEST : ";
    static const int my_sd_len     = my_sd.length(); 
    static const int hi_sd_len     = hi_sd.length();

    std::string my_sn      = my_score_.get_string();
    int my_sn_len                  = my_sn.length();
    std::string hi_sn;
    int hi_sn_len;
    
    if (winning_) {
        hi_sn     = my_score_.get_string();
        hi_sn_len = my_sn.length();
    } else {
        hi_sn     = hi_score_.get_string();
        hi_sn_len = hi_sn.length();
    }

    int game_width = gb_.width_ * gb_.attr_.block_width_;
    int left, half_left1, half_left2;
    
    std::string line = "";

    // Decides how much of the score to print out given how many
    // characters long the board is. (Probably more hard-coded than
    // it should be)
    if ((left = game_width - my_sd_len - my_sn_len  
                    - hi_sd_len - hi_sn_len - 1) >= 0) {
        // display full score along with best score
        line += my_color;
        if (winning_) line += "\033[1m";
        line += my_sd + my_sn;
        
        half_left1  = (game_width >> 1) - my_sd_len - my_sn_len - 1;
        half_left1 += (game_width  & 1);
        half_left2  = (game_width >> 1) - hi_sd_len - hi_sn_len;
       
        if (half_left1 < 0) half_left2 += half_left1;
        else if (half_left2 < 0 ) half_left1 += half_left2;
        for (int i = 0; i < half_left1; ++i) {line += " ";}

        line += "\033[0m";
        line += "|"; 
        line += hi_color;
        if (winning_) line += "\033[1m";
        line += hi_sd + hi_sn;
        for (int i = 0; i < half_left2; ++i) {line += " ";}
        line += "\033[0m";
        return line;
    } else if ((left = game_width - my_sd_len 
            - my_sn_len) >= 0) { 
        // show full score
        line += my_color;
        if (winning_) line += "\033[1m";
        line += my_sd + my_sn;
        line += "\033[0m";
    } else if ((left = game_width - my_sn_len) >= 0) { 
        // just show score number
        line += my_color;
        if (winning_) line += "\033[1m";
        line += my_sn;
        line += "\033[0m";

    } else if ((left = game_width - 1) >=0 ) {    
        // I think you only get here if something has gone wrong
        line += my_color;
        if (winning_) line += "\033[1m";
        line += "!";
        line += "\033[0m";
    } else {
        return line;
    }

    for (int i = 0; i < left; ++i) line += " ";
    return line;
}

std::ostream & operator << 
(std::ostream &o, Game& g)
{   
    int numclear = g.gb_.height_ + 4;
    for (int i = 0; i < numclear+1; ++i) {
        o << "\033[1A";
    } 
   
    if (g.gb_.attr_.update_block_width_) {
        g.gb_.update_block_width();
    }

    o << "\033[K\033[1B";
    o << g.divider('+','-') <<  "\033[K" << std::endl; 
    o << g.gb_;
    o << g.divider('+','-') <<  "\033[K" << std::endl; 
    o << "\033[K|" << g.score_line() << "|" << std::endl;
    o << g.divider('+','-') <<  "\033[K" << std::endl;
    o << "\033[K"; 
    return o;
}


