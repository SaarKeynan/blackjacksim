//
// Created by Saar Keynan on 02/03/2022.
//

#ifndef CPPBJ_CONDITION_H
#define CPPBJ_CONDITION_H

#include "CmpType.h"
class ConditionObject;

class Condition {
    ConditionObject *firstCond;
    ConditionObject *secondCond;
    CmpType comparison;
    public:
        bool evaluate();
};

#endif //CPPBJ_CONDITION_H
