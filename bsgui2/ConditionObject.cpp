//
// Created by Saar Keynan on 02/03/2022.
//

#include <string>
#include "ConditionObject.h"

ConditionObject::ConditionObject(std::string name, void *object, ConditionObjType type) {
	this->name = name;
	this->object = object;
    this->type = type;
}

bool ConditionObject::evaluate(ConditionObject other, CmpType comparison) {
    if(type != other.type) {
        return comparison == NEQ;
    }
    switch(type) {
        case BOOLEAN: {
            switch (comparison) {
                case EQ:
                    return *(bool *)object == *(bool *) other.object;
                case NEQ:
                    return *(bool *)object != *(bool *) other.object;
                default:
                    return false;
            }
        }
        case NUMBER: {
            switch (comparison) {
                case EQ:
                    return *(double *)object == *(double *) other.object;
                case NEQ:
                    return *(double *)object != *(double *) other.object;
                case GT:
                    return *(double *)object > *(double *) other.object;
                case LT:
                    return *(double *)object < *(double *) other.object;
                case GEQ:
                    return *(double *)object >= *(double *) other.object;
                case LEQ:
                    return *(double *)object <= *(double *) other.object;
            }
        }
    }
}