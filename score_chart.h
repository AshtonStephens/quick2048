/* 
 *  score_chart.h
 *  
 *  purpose: to
 *
 *
 */

#ifndef SCORE_CHART_H
#define SCORE_CHART_H
#define NUM_SCORES

#include <vector>
#include <string>

class scorechart 
{
public:
    scorechart();
    ~scorechart();
    std::string line(int);

private:

    struct HighScore {
        std::string name;
        Score      score;
    }

    HighScore highscores[NUM_SCORES];

}


#endif
