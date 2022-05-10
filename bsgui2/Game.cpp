//
// Created by Saar Keynan on 27/02/2022.
//

#include "Game.h"

Game::Game(Rules rules) {
    this->rules = rules;
	this->hardTable = BSTable(18, 10, [](int a) {return a - 3; });
	this->softTable = BSTable(7, 10, [](int a) { return a - 13; });
	this->splitTable = BSTable(10, 10, [](int a) { return a / 2; });
}

Card Game::drawCard() {
    int index = rand() % deck.size;
    Card card = deck.get(index);
    deck.remove(index);
    return card;
}