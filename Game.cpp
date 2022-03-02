//
// Created by Saar Keynan on 27/02/2022.
//

#include "Game.h"


Game::Game(Rules rules) {
    this->rules = rules;
}
Card Game::drawCard() {
    int index = rand() % deck.size;
    Card card = deck.get(index);
    deck.remove(index);
    return card;
}