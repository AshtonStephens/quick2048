
#include <stdlib.h>
#include "board.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

using namespace std;

static int LEFT_TRIGGER    = 'a';
static int RIGHT_TRIGGER   = 'd';
static int UP_TRIGGER      = 'w';
static int DOWN_TRIGGER    = 's';

void reset_read ();
int loop_on_input();
void setup_instant_read();

int main (int argc, char **argv)
{
    return loop_on_input();
}


int loop_on_input()
{
    char temp;
    Board board(4,4,2);
    setup_instant_read();
    // loop on reading in and then printing
    temp = fgetc(stdin);
    while (temp != 'q') {
        switch (temp) {
            case LEFT_TRIGGER:
                cout << "left";
                break;
            case RIGHT_TRIGGER:
                cout << "rightt";
                break;       
            case UP_TRIGGER:
                cout << "up";
                break;
            case DOWN_TRIGGER:
                cout << "down";
                break;
        
        } 
        cout << board;
         
        
        
        temp = fgetc(stdin);
    }
    reset_read ();
    return 1;
}

void setup_instant_read() 
{
    struct termios old = {0};
    
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");

    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
}

void reset_read () {
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    old.c_cc[VMIN]  = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
}


