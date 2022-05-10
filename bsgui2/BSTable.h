#pragma once
#include <iostream>
#include "BSTableCell.h"
#include "ConditionObject.h"
#include "Hand.h"
#include "Globals.h"
#include <functional>

class BSTable {
	int rowNum;
	int colNum;
	std::function<int(int)> rowMatch; //converts sum into rows
	BSTableCell *table;
	int getIndex(int col, int row);
public:
	BSTable();
	BSTable(BSTableCell* cells, int row, int col, std::function<int(int)> rowMatch);
	BSTable(int row, int col, std::function<int(int)> rowMatch);
	std::string toString(ConditionObject *globals, int length);
	void setTable(BSTableCell* cells);
	Move decide(Hand hand, Card dealer);
};

