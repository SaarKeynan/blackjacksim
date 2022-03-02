//
// Created by Saar Keynan on 26/02/2022.
//

#ifndef CPPBJ_PLAYER_H
#define CPPBJ_PLAYER_H

#include "List.h"
#include "Hand.h"
#include "Game.h"

class Player {
    public:
        double money;
        bool robot;
        List<Hand> hands;
        Player(int money, bool robot);
        List<Move> Player::getMoves(Hand hand);
        void doMove(Hand hand, Move move, Game &game);
        void playHand(Hand h, Game &game);
};


#endif //CPPBJ_PLAYER_H
