






#include "board.h"
#include <string>
#include <iostream>

using namespace std;

static int LEFT_TRIGGER    = 'a';
static int RIGHT_TRIGGER   = 'd';
static int UP_TRIGGER      = 'w';
static int DOWN_TRIGGER    = 's';

int loop_on_input();

int main (int argc, char **argv)
{
    return loop_on_input();
}


int loop_on_input()
{
    Board board(4,4,2);
    cout << board << endl;
}




