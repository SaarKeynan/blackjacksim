//
// Created by Saar Keynan on 26/02/2022.
//

#include "Player.h"

Player::Player(int money, bool robot) {
    this->money = money;
    this->robot = robot;
    this->hands = List<Hand>();
}

List<Move> Player::getMoves(Hand hand) {
    List<Move> moves = List<Move>();
    moves.add(STAND);
    moves.add(HIT);
    if (hand.cards.size == 2 && money > hand.bet) { //TODO: Add maximum doubles after split, splitting aces, etc
        moves.add(DOUBLE);
        if (hand.cards.get(0).value() == hand.cards.get(1).value()) {
            moves.add(SPLIT);
        }
    }
    return moves;
}

void Player::doMove(Hand hand, Move move, Game &game) {
    switch (move) {
        case STAND: {
            hand.status = INACTIVE;
            break;
        }
        case HIT: {
            hand.cards.add(game.drawCard());
            break;
        }
        case DOUBLE: {
            hand.cards.add(game.drawCard());
            money -= hand.bet;
            hand.bet *= 2;
            hand.status = INACTIVE;
            break;
        }
        case SPLIT: {
            Hand newHand = Hand(hand.bet);
            newHand.cards.add(hand.cards.get(1));
            hand.cards.remove(1);
            hand.cards.add(game.drawCard());
            newHand.status = STANDBY;
            hands.add(newHand);
            break;
        }
        case SURRENDER: {
            money -= hand.bet / 2;
            hand.status = INACTIVE;
            break;
        }
    }
}

void Player::playHand(Hand h, Game &game) {
    List<Move> moves = getMoves(h);
    if(robot) {
        doMove(h, moves.get(rand() % moves.size), game);
    } else {
        doMove(h, moves.get(rand() % moves.size), game);
    }
}
