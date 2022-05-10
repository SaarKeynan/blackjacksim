#pragma once

#include "Globals.h"

struct InputTable {
	int rowNum;
	int colNum;
	char* defValue; //default values for the table
	char* table;
	std::function<std::string(int)> nameFunc; //gets name of row
	InputTable(int row, int col, std::function<std::string(int)> nameFunc, char* defValue) {
		this->rowNum = row;
		this->colNum = col;
		this->table = (char *)calloc(row * col * COND_NAME_LEN, 1);
		this->defValue = defValue;
		this->nameFunc = nameFunc;
	}
};