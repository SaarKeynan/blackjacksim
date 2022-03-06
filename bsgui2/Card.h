//
// Created by Saar Keynan on 25/02/2022.
//

#ifndef CPPBJ_CARD_H
#define CPPBJ_CARD_H
#include "Suit.h"
#include "Rank.h"

struct Card {
    Rank rank;
    Suit suit;
public:
    int value() {
        switch (rank) {
            case ACE:
                return 1;
            case TWO:
                return 2;
            case THREE:
                return 3;
            case FOUR:
                return 4;
            case FIVE:
                return 5;
            case SIX:
                return 6;
            case SEVEN:
                return 7;
            case EIGHT:
                return 8;
            case NINE:
                return 9;
            case TEN:
                return 10;
            case JACK:
                return 10;
            case QUEEN:
                return 10;
            case KING:
                return 10;
        }
        return 0;
    }
};



#endif //CPPBJ_CARD_H
