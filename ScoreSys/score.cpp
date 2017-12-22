

#include "score.h"

Score::~Score()
{
}

void Score::operator += (int index)
{
    while (score_vector_.size() <= index) score_vector_.push_back(0);
    score_vector_.at(index) += 1;
    updated_ = true;
}
    
void Score::set_power (int power)
{
    if (power != power_) {
        updated_ = true;
        power_   = power;
    }
}

std::string Score::get_string ()
{
    if (updated_) {
        updated_ = false;
        value_   = calculated_score();
        str_ = std::to_string(value_);
    } 
    return str_; 
}

int Score::get_value ()
{
    if (updated_) {
        updated_ = false;
        value_   = calculated_score();
        str_ = std::to_string(value_);
    } 
    return value_;
}

// returns val to the power of pow
int power_opp (const int val, const int pow)
{
    int ret = 1;
    for (int i = 0; i < val; ++i)
        ret *= pow;
    return ret; 
}

int Score::calculated_score ()
{
    int calc_score = 0;
    int size = score_vector_.size();
    for (int i = 0; i < size; ++i) {
        calc_score += score_vector_[i] * power_opp (i,power_);
    }
    return calc_score;
}

std::ostream & operator << (std::ostream &o, const Score &s)
{
    int size = s.score_vector_.size();
    for (int i = 0; i < size; ++i) {
        o << i << "," << s.score_vector_[i] << ";";
    }
}







