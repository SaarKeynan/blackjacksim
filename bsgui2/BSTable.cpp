#include "BSTable.h"

BSTable::BSTable(BSTableCell *cells, int row, int col) {
	this->table = cells;
	this->rowNum = row;
	this->colNum = col;
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

int BSTable::getIndex(int row, int col) {
	return row * this->colNum + col;
}
