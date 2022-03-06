//
// Created by Saar Keynan on 02/03/2022.
//

#include "BSTableCell.h"

BSTableCell::BSTableCell(Condition *conditions, Move *moves, int count) {
    this->conditions = conditions;
    this->moves = moves;
    this->count = count;
}

Move BSTableCell::decide() {
    for(int i = 0; i < count; i++) {
        if(conditions[i].evaluate()) {
            return moves[i];
        }
    }
    return moves[count];
}