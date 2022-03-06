//
// Created by Saar Keynan on 02/03/2022.
//

#ifndef CPPBJ_CONDITIONOBJECT_H
#define CPPBJ_CONDITIONOBJECT_H

#include <string>
#include "ConditionObjType.h"
#include "CmpType.h"
#include "Condition.h"

class ConditionObject {
	std::string name;
    void *m_Object;
    ConditionObjType m_Type;
public:
    ConditionObject(std::string name, void *object, ConditionObjType type);
    bool evaluate(ConditionObject other, CmpType comparison);
};

#endif //CPPBJ_CONDITIONOBJECT_H
