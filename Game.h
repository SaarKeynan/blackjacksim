//
// Created by Saar Keynan on 27/02/2022.
//

#ifndef CPPBJ_GAME_H
#define CPPBJ_GAME_H

#include "Rules.h"
#include "Card.h"
#include "List.h"
#include <cstdlib>

class Player;
class Game {
    Rules rules;
    List<Card> deck;
    List<Player> players;
    public:
        Game(Rules rules);
        Card drawCard();
};

#endif //CPPBJ_GAME_H
