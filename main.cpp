
#include <stdlib.h>
#include "game.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

using namespace std;

static const char LEFT_TRIGGER    = 'a';
static const char RIGHT_TRIGGER   = 'd';
static const char UP_TRIGGER      = 'w';
static const char DOWN_TRIGGER    = 's';
static const char END_GAME        = 'q';
static const char RESIZE_TRIGGER  = 'r';

int instant_read ();
int game_loop  (Game &game);
int resize_loop(Game &game);

int main (int argc, char **argv)
{
    srand(time(NULL));
    Game game(4,4,2);
    int gamevalue = game_loop(game);
    cout << "Game over!"   << endl;
    cout << "Your Score: " << game.my_score_.get_value() << endl;
}

int resize_loop(Game &game)
{
    static const std::string bgd = "40;37;7;2";
    Game show_game(game);
    
    show_game.gb_.attr_.background_data_ = bgd;
    std::cout << show_game;
    
    int  width  = game.gb_.width_ ;
    int  height = game.gb_.height_;

    bool changes = true;
    char temp    = instant_read();

    while (temp != RESIZE_TRIGGER) {
        switch (temp) {
            case LEFT_TRIGGER:
                if (width > 0) --width; 
                break;
            case RIGHT_TRIGGER:
                ++width; 
                break;       
            case UP_TRIGGER:
                ++height; 
                break;
            case DOWN_TRIGGER:
                if (height > 0) --height; 
                break;
            case END_GAME:
                return true;
            default:
                changes = false;
                break; 
        }
        
        if (temp >= '0' && temp <= '9') {
            changes = true;
            if (temp == '0') temp = '9'+1;
            show_game.set_power(temp - '0');
        }
        
        if (changes) {
            show_game = game;
            show_game.gb_.attr_.background_data_ = bgd;
            show_game.resize(width,height);
            std::cout << show_game;
        }

        temp = instant_read();
    }
    game.resize(width,height);
    return false;
}


int game_loop(Game &game)
{
    char temp;
    bool changes  = true;
    bool gameover = false;
    // loop on reading in and then printing
    
    cout << "\033[?25l";
    cout << "\033[6B";
    
    game.addRandom();
    cout << game;
    while (!gameover) {
        temp = instant_read();
        switch (temp) {
            case LEFT_TRIGGER:
                changes = game.move_left();
                break;
            case RIGHT_TRIGGER:
                changes = game.move_right();
                break;       
            case UP_TRIGGER:
                changes = game.move_up();
                break;
            case DOWN_TRIGGER:
                changes = game.move_down();
                break;
            case RESIZE_TRIGGER:
                gameover = resize_loop(game);
                cout << game;
                if (game.gb_.num_filled() != 0) {
                    changes = false;
                }
                break;
            case END_GAME:
                gameover = true; 
                break;
            default:
                changes = false;
                break; 
        }

        if (temp >= '0' && temp <= '9') {
            if (temp == '0') temp = '9'+1;
            game.set_power(temp - '0');
            cout << game;
        }
        if (changes) {
            game.addRandom();
            cout << game;
            if (game.over()) {
                gameover = true;
            }
        }
    }
    cout << "\033[?25h";
    return 1;
}

int instant_read() 
{
    struct termios attr = {0};
    int temp;

    if (tcgetattr(0, &attr) < 0)
        perror("tcsetattr()");

    attr.c_lflag &= ~ICANON;
    attr.c_lflag &= ~ECHO;
    attr.c_cc[VMIN] = 1;
    attr.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &attr) < 0)
        perror("tcsetattr ICANON");
    
    temp = fgetc(stdin);
    
    attr.c_lflag |= ICANON;
    attr.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &attr) < 0)
        perror ("tcsetattr ~ICANON");
    return temp;
}

