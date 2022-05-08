//
// Created by Saar Keynan on 02/03/2022.
//

#ifndef CPPBJ_CONDITIONOBJECT_H
#define CPPBJ_CONDITIONOBJECT_H

#include <string>
#include "ConditionObjType.h"
#include "CmpType.h"

class ConditionObject {
public:
	void* object;
	std::string name;
	ConditionObjType type;

    ConditionObject(std::string name, void *object, ConditionObjType type);
    bool evaluate(ConditionObject other, CmpType comparison);
};

#endif //CPPBJ_CONDITIONOBJECT_H
