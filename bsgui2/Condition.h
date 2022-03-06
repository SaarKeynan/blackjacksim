//
// Created by Saar Keynan on 02/03/2022.
//

#ifndef CPPBJ_CONDITION_H
#define CPPBJ_CONDITION_H

#include "CmpType.h"
class ConditionObject;

class Condition {
    ConditionObject *m_FirstCond;
    ConditionObject *m_SecondCond;
    CmpType m_Comparison;
    public:
        bool evaluate();
		char *toString(ConditionObject objects[], int size);
};

#endif //CPPBJ_CONDITION_H
