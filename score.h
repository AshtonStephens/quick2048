


#ifndef SCORE_H
#define SCORE_H

#include <vector>
#include <iostream>

class Score {
public:
    Score() : updated_(false), power_(0), value_(0) {};
    ~Score();
    void operator += (int); 
    int  get_value ();
    void set_power (int power);
private:
    std::vector <int> score_vector_;
    int calculated_score ();
    bool updated_;
    int power_;
    int value_;
};

#endif
