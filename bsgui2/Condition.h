//
// Created by Saar Keynan on 02/03/2022.
//

#ifndef CPPBJ_CONDITION_H
#define CPPBJ_CONDITION_H

#include <iostream>
#include "CmpType.h"

class ConditionObject;

class Condition {
    int m_FirstCond;
    int m_SecondCond;
    CmpType m_Comparison;
    public:
		std::string toString();
		bool evaluate(ConditionObject objects[]);
		Condition(int firstObj, int secondObj, CmpType comparison);
		Condition fromString(std::string str, ConditionObject objects[]);
};

#endif //CPPBJ_CONDITION_H
