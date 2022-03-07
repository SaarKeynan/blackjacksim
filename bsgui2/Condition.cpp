//
// Created by Saar Keynan on 02/03/2022.
//

#include "Condition.h"
#include "ConditionObject.h"

Condition::Condition(ConditionObject* firstObj, ConditionObject* secondObj, CmpType comparison) {
	m_FirstCond = firstObj;
	m_SecondCond = secondObj;
	m_Comparison = comparison;
}

bool Condition::evaluate() {
    return m_FirstCond->evaluate(*m_SecondCond, m_Comparison);
}

Condition Condition::fromString(std::string str, ConditionObject objects[]) {
	int firstIndex = -1;
	int secondIndex = -1;
	CmpType comparison = EQ;
	if (sscanf_s(str.c_str(), "{%d,%d,%d}", &firstIndex, &secondIndex, &comparison) == NULL) {
		//add support for nested conditions here probably.
	}
	return Condition(&objects[firstIndex], &objects[secondIndex], comparison);
}

char *Condition::toString(ConditionObject objects[], int size) {
	if (m_FirstCond->type != CONDITION && m_SecondCond->type != CONDITION) {
		int firstIndex = -1;
		int secondIndex = -1;
		for (int i = 0; i < size; i++) {
			if (m_FirstCond == &objects[i]) {
				firstIndex = i;
			}
			if (m_SecondCond == &objects[i]) {
				secondIndex = i;
			}
		}
		int length = snprintf(NULL, 0, "{%d,%d,%d}", firstIndex, secondIndex, m_Comparison);
		char *str = (char *)malloc(length);
		sprintf_s(str, length, "{%d,%d,%d}", firstIndex, secondIndex, m_Comparison);
		return str;
	}
	else {
		int length = snprintf(NULL, 0, "{%s,%s,%d}", ((Condition *)m_FirstCond)->toString(objects, size), ((Condition*)m_SecondCond)->toString(objects, size), m_Comparison);
		char* str = (char*)malloc(length);
		sprintf_s(str, length, "{%s,%s,%d}", ((Condition*)m_FirstCond)->toString(objects, size), ((Condition*)m_SecondCond)->toString(objects, size), m_Comparison);
		return str;
	}
}