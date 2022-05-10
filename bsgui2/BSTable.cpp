#include "BSTable.h"

BSTable::BSTable() {
	this->table = nullptr;
	this->rowNum = 0;
	this->colNum = 0;
	this->rowMatch = NULL;
}

BSTable::BSTable(BSTableCell *cells, int row, int col, std::function<int(int)> rowMatch) {
	this->table = cells;
	this->rowNum = row;
	this->colNum = col;
	this->rowMatch = rowMatch;
}

BSTable::BSTable(int row, int col, std::function<int(int)> rowMatch) {
	this->rowNum = row;
	this->colNum = col;
	this->table = nullptr;
	this->rowMatch = rowMatch;
}

std::string BSTable::toString(ConditionObject *globals, int length) {
	std::string str = "(";
	for (int i = 0; i < rowNum; i++) {
		for (int j = 0; j < colNum; j++) {
			str.append(table[getIndex(i,j)].toString());
		}
	}
	str.append(")");
	return str;
}

Move BSTable::decide(Hand hand, Card dealer) {
	int column = dealer.rank == ACE ? 9 : dealer.value()-2;
	int row = this->rowMatch(hand.value().value);
	return table[getIndex(row, column)].decide(objects);
}

void BSTable::setTable(BSTableCell* cells) {
	this->table = cells;
}

int BSTable::getIndex(int row, int col) {
	return row * this->colNum + col;
}
