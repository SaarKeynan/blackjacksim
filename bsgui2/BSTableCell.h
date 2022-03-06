//
// Created by Saar Keynan on 01/03/2022.
//

#ifndef CPPBJ_BSTABLECELL_H
#define CPPBJ_BSTABLECELL_H

#include <string>
#include "Condition.h"
#include "Move.h"

class BSTableCell {
    std::string name;
    Condition *conditions;
    int count;
    Move *moves;
public:
    BSTableCell(Condition *conditions, Move *moves, int count);
    Move decide();
};

#endif //CPPBJ_BSTABLECELL_H
