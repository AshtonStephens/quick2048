
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>

#include <unistd.h>
#include <time.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include "score_chart.h"

using namespace std;

static const char LEFT_TRIGGER    = 'a';
static const char RIGHT_TRIGGER   = 'd';
static const char UP_TRIGGER      = 'w';
static const char DOWN_TRIGGER    = 's';
static const char END_GAME        = 'q';
static const char RESIZE_TRIGGER  = 'r';

int instant_read ();
int score_tests  ();

int main (int argc, char **argv)
{
    srand(time(NULL));
    string filename;

    for (int i = 0; i < argc; ++i) 
    {
        if (strcmp(argv[i],(char*)"-f")==0) {
            filename = (char*)argv[++i];
        }
    }

    int nsize = 10;
    char *somedata;
    ofstream myfile;
    myfile.open(filename);
    myfile << "poop!" << endl;
    myfile.close();
}

int score_tests () 
{

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

