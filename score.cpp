/*
 * score.cpp
 *
 * Implementation of the score. Handles calculating of score for different
 * power systems.
 * 
 * by: Ashton Stephens
 * date: 12-18-17
 * documented: 3-23-19
 *
 */

#include "score.h"

Score::~Score()
{
}

// adds the index created to the score vector
void Score::operator += (int index)
{
    // Increase the size of the score vector if the index doesn't
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

