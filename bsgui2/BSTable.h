#pragma once
#include <iostream>
#include "BSTableCell.h"
#include "ConditionObject.h"
#include "Hand.h"
#include "Globals.h"

class BSTable {
	int offset; //offset of value-index.
	int rowNum;
	int colNum;
	BSTableCell *table;
	int getIndex(int col, int row);
public:
	std::string toString(ConditionObject *globals, int length);
	BSTable(BSTableCell *cells, int row, int col);
	Move decide(Hand hand, Card dealer);
};

