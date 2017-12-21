
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

int instant_read ();
int loop_on_input();

int main (int argc, char **argv)
{
    srand(time(NULL));
    return loop_on_input();
}

int loop_on_input()
{
    char temp;
    bool changes = true;
    Game game(4,4,2);
    // loop on reading in and then printing
    
    cout << "\033[6B";
    game.addRandom();
    cout << game;
    temp = instant_read();
    while (temp != 'q') {
        // 
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
            default:
                changes = false;
                break; 
        }

        if (temp >= '0' && temp <= '9') {
            game.set_power(temp - '0');
            cout << game;
        }

        if (changes) {
        
            game.addRandom();
            cout << game;
            if (game.over()) exit(EXIT_SUCCESS); 

        }
        temp = instant_read();
    }
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

