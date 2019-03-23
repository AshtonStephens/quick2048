/*
 * score.h
 *
 * Interface for the score. Handles calculating of score for different
 * power systems.
 * 
 * by: Ashton Stephens
 * date: 12-18-17
 * documented: 3-23-19
 *
 */

#ifndef SCORE_H
#define SCORE_H

#include <vector>
#include <iostream>

/* 
 * Score
 *
 * methodology:
 * in order to store the score in a way that allows for it to be
 * converted between different base systems, we store the score 
 * of the game in a vector where the ith spot holds the number of 
 * times a block of power i has been created by the merging of two
 * blocks.
 *
 * to calculate the score:
 * sum ( (base^i) * vector[i]) for all i in vector
 *
 */
class Score {
public:
    Score() : updated_(false), power_(0), value_(0) {};
    ~Score();
    void operator += (int); 
    int  get_value ();
    std::string get_string ();
    void set_power (int power);
private:
    std::vector <int> score_vector_;
    int calculated_score ();
    bool updated_;
    int power_;
    int value_;
    std::string str_;
};

#endif
