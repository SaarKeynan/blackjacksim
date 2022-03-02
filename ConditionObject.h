//
// Created by Saar Keynan on 02/03/2022.
//

#ifndef CPPBJ_CONDITIONOBJECT_H
#define CPPBJ_CONDITIONOBJECT_H

#include "ConditionObjType.h"
#include "CmpType.h"
#include "Condition.h"

struct ConditionObject {
    void *object;
    ConditionObjType type;
    bool evaluate(ConditionObject other, CmpType comparison) {
        if(type != other.type) {
            return comparison == NEQ;
        }
        switch(type) {
            case BOOLEAN: {
                switch (comparison) {
                    case EQ:
                        return *(bool *) object == *(bool *) other.object;
                    case NEQ:
                        return *(bool *) object != *(bool *) other.object;
                    default:
                        return false;
                }
            }
            case NUMBER: {
                switch (comparison) {
                    case EQ:
                        return *(double *) object == *(double *) other.object;
                    case NEQ:
                        return *(double *) object != *(double *) other.object;
                    case GT:
                        return *(double *) object > *(double *) other.object;
                    case LT:
                        return *(double *) object < *(double *) other.object;
                    case GEQ:
                        return *(double *) object >= *(double *) other.object;
                    case LEQ:
                        return *(double *) object <= *(double *) other.object;
                }
            }
            case CONDITION: {
                switch (comparison) {
                    case EQ:
                        return (*(Condition *)object).evaluate() == (*(Condition *)other.object).evaluate();
                    case NEQ:
                        return (*(Condition *)object).evaluate() != (*(Condition*)other.object).evaluate();
                    default:
                        return false;
                }
            }
        }
    }
};

#endif //CPPBJ_CONDITIONOBJECT_H
