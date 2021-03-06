//
// Created by Saar Keynan on 25/02/2022.
//

#include "Hand.h"

Hand::Hand(double bet) {
    this->cards = List<Card>();
    this->bet = bet;
}

HandValue Hand::value() {
    int value = 0;
    bool ace = false;
    for (int i = 0; i < this->cards.size; i++) {
        value += this->cards.get(i).value();
        if(this->cards.get(i).value() == 1) {
			ace = true;
        }
    }
	if (value <= 11 && ace) {
		return HandValue(value + 10, true);
    }
    return HandValue(value, true);
}