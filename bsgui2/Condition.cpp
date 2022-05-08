//
// Created by Saar Keynan on 02/03/2022.
//

#include "Condition.h"
#include "ConditionObject.h"

Condition::Condition(int firstObj, int secondObj, CmpType comparison) {
	m_FirstCond = firstObj;
	m_SecondCond = secondObj;
	m_Comparison = comparison;
}

std::string Condition::toString() {
	int length = snprintf(NULL, 0, "{%d,%d,%d}", m_FirstCond, m_SecondCond, m_Comparison) + 1;
	char* str = (char*)malloc(length);
	sprintf_s(str, length, "{%d,%d,%d}", m_FirstCond, m_SecondCond, m_Comparison);
	//printf("aaaaa\n%s\n", str);
	return std::string(str);
}

bool Condition::evaluate(ConditionObject objects[]) {
	return objects[m_FirstCond].evaluate(objects[m_SecondCond], m_Comparison);
}

Condition Condition::fromString(std::string str, ConditionObject objects[]) {
	int firstIndex = -1;
	int secondIndex = -1;
	CmpType comparison = EQ;
	return Condition(firstIndex, secondIndex, comparison);
}