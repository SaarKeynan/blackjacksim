#pragma once
#include <iostream>
#include "BSTableCell.h"
#include "ConditionObject.h"

class BSTable {
	int rowNum;
	int colNum;
	BSTableCell *table;
	int getIndex(int col, int row);
public:
	std::string toString(ConditionObject *globals, int length);
	BSTable(BSTableCell *cells, int row, int col);
};

