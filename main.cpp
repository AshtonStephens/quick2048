
#include <stdlib.h>
#include "board.h"
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
    Board board(4,4,2);
    // loop on reading in and then printing
    
    
    
    temp = instant_read();
    cout << "\033[s";
    board.addRandom();
    cout << "\033[6B";
    cout << board;
    while (temp != 'q') {
        // 
        switch (temp) {
            case LEFT_TRIGGER:
                changes = board.move_left();
                break;
            case RIGHT_TRIGGER:
                changes = board.move_right();
                break;       
            case UP_TRIGGER:
                changes = board.move_up();
                break;
            case DOWN_TRIGGER:
                changes = board.move_down();
                break;
            default:
                changes = false;
                break; 
        }

        if (temp >= '0' && temp <= '9') {
            board.set_power(temp - '0');
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
            cout << board;
        }

        if (changes) {
            
            if(!board.addRandom()) {
                exit(EXIT_FAILURE);
            }
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
            cout << board;
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

