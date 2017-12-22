/* 
 *  score_chart.h
 *  
 *  purpose: to
 *
 *
 */

#ifndef SCORE_CHART_H
#define SCORE_CHART_H

#define NUM_SCORES 5

#include <vector>
#include <iostream>
#include <string>
#include "score.h"

class scorechart 
{
public:
    scorechart();
    ~scorechart();
    std::string line(int);
    
    int read  (std::istream &i);
    int write (std::ostream &o);

    friend std::ostream & operator << (std::ostream &o, const scorechart &s);

private:

    struct HighScore {
        std::string name;
        Score      score;
    };

    HighScore highscores[NUM_SCORES];
};

#endif
