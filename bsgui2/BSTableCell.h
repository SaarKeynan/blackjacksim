//
// Created by Saar Keynan on 01/03/2022.
//

#ifndef CPPBJ_BSTABLECELL_H
#define CPPBJ_BSTABLECELL_H

#include <string>
#include "ConditionObject.h"
#include "Condition.h"
#include "Move.h"

class BSTableCell {
    std::string name;
    Condition *conditions;
    int count;
    Move *moves;
public:
	BSTableCell();
	BSTableCell(Condition *conditions, Move *moves, int count);
    BSTableCell(const BSTableCell &other);
	BSTableCell& operator=(const BSTableCell& other);
	Move decide(ConditionObject objects[]);
    std::string toString();
	int getCount() {
		return count;
	}
};

#endif //CPPBJ_BSTABLECELL_H
