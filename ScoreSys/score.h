


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
    std::string get_string ();
    void set_power (int power);
    friend std::ostream & operator << (std::ostream &o, const Score &s);
private:
    std::vector <int> score_vector_;
    int calculated_score ();
    bool updated_;
    int power_;
    int value_;
    std::string str_;
};

#endif
