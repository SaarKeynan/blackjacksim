//
// Created by Saar Keynan on 25/02/2022.
//

#ifndef CPPBJ_HAND_H
#define CPPBJ_HAND_H

#include "List.h"
#include "Card.h"
#include "Move.h"
#include "Status.h"

class Hand {
public:
    List<Card> cards;
    double bet;
    Status status;
    Hand(double bet);
    int value();
};


#endif //CPPBJ_HAND_H
