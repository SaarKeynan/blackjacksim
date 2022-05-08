//
// Created by Saar Keynan on 02/03/2022.
//

#include "BSTableCell.h"

BSTableCell::BSTableCell() {
	this->conditions = nullptr;
	this->moves = nullptr;
	this->count = -1;
}

BSTableCell::BSTableCell(Condition *conditions, Move *moves, int count) {
    this->conditions = conditions;
    this->moves = moves;
    this->count = count;
}

BSTableCell::BSTableCell(const BSTableCell &other) {
	this->conditions = other.conditions;
	this->moves = other.moves;
	this->count = other.count;
}

BSTableCell& BSTableCell::operator=(const BSTableCell &other) {
	this->conditions = other.conditions;
	this->moves = other.moves;
	this->count = other.count;
	return *this;
}

std::string BSTableCell::toString() {
	std::string result = "[";
	for (int i = 0; i < count; i++) {
		result.append(conditions[i].toString());
		if (i != count - 1) {
			result.append(",");
		}
	}
	result.append("{");
	for (int i = 0; i < count; i++) {
		result.append(std::to_string(moves[i]));
		if (i != count - 1) {
			result.append(",");
		}
	}
	result.append("}");
	result.append("]");
	return result;
}

Move BSTableCell::decide(ConditionObject objects[]) {
    for(int i = 0; i < count; i++) {
        if(conditions[i].evaluate(objects)) {
            return moves[i];
        }
    }
    return moves[count];
}