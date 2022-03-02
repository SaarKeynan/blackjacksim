//
// Created by Saar Keynan on 26/02/2022.
//

#ifndef CPPBJ_RULES_H
#define CPPBJ_RULES_H

struct Rules {
    bool SPLIT_ACES;
    bool RESPLIT_ACES;
    bool DOUBLE_AFTER_SPLIT;
    bool SURRENDER;
    bool HIT_AFTER_SPLIT_ACES;
    int DOUBLE_AMOUNT;
    int RESPLIT_AMOUNT;
    int DECK_AMOUNT;
    double BLACKJACK_RATIO;
    double DECK_PENETRATION;
    Rules(bool splitAces, bool resplitAces, bool doubleAfterSplit, bool surrender, int hitAfterSplitAces, int doubleAmount, int resplitAmount, int deckAmount, double blackjackRatio, double deckPenetration) {
        SPLIT_ACES = splitAces;
        RESPLIT_ACES = resplitAces;
        DOUBLE_AFTER_SPLIT = doubleAfterSplit;
        SURRENDER = surrender;
        HIT_AFTER_SPLIT_ACES = hitAfterSplitAces;
        DOUBLE_AMOUNT = doubleAmount;
        RESPLIT_AMOUNT = resplitAmount;
        DECK_AMOUNT = deckAmount;
        BLACKJACK_RATIO = blackjackRatio;
        DECK_PENETRATION = deckPenetration;
    }
    Rules(Rules const &r) {
        SPLIT_ACES = r.SPLIT_ACES;
        RESPLIT_ACES = r.RESPLIT_ACES;
        DOUBLE_AFTER_SPLIT = r.DOUBLE_AFTER_SPLIT;
        SURRENDER = r.SURRENDER;
        HIT_AFTER_SPLIT_ACES = r.HIT_AFTER_SPLIT_ACES;
        DOUBLE_AMOUNT = r.DOUBLE_AMOUNT;
        RESPLIT_AMOUNT = r.RESPLIT_AMOUNT;
        DECK_AMOUNT = r.DECK_AMOUNT;
        BLACKJACK_RATIO = r.BLACKJACK_RATIO;
        DECK_PENETRATION = r.DECK_PENETRATION;
    }
    Rules() {
        SPLIT_ACES = true;
        RESPLIT_ACES = true;
        DOUBLE_AFTER_SPLIT = true;
        SURRENDER = true;
        HIT_AFTER_SPLIT_ACES = true;
        DOUBLE_AMOUNT = -1;
        RESPLIT_AMOUNT = -1;
        DECK_AMOUNT = 6;
        BLACKJACK_RATIO = 1.5;
        DECK_PENETRATION = 0;
    }
};

#endif //CPPBJ_RULES_H
