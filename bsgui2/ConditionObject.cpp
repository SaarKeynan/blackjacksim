//
// Created by Saar Keynan on 02/03/2022.
//

#include <string>
#include "ConditionObject.h"

ConditionObject::ConditionObject(std::string name, void *object, ConditionObjType type) {
	this->name = name;
	this->m_Object = object;
    this->m_Type = type;
}

bool ConditionObject::evaluate(ConditionObject other, CmpType comparison) {
    if(m_Type != other.m_Type) {
        return comparison == NEQ;
    }
    switch(m_Type) {
        case BOOLEAN: {
            switch (comparison) {
                case EQ:
                    return *(bool *) m_Object == *(bool *) other.m_Object;
                case NEQ:
                    return *(bool *)m_Object != *(bool *) other.m_Object;
                default:
                    return false;
            }
        }
        case NUMBER: {
            switch (comparison) {
                case EQ:
                    return *(double *)m_Object == *(double *) other.m_Object;
                case NEQ:
                    return *(double *)m_Object != *(double *) other.m_Object;
                case GT:
                    return *(double *)m_Object > *(double *) other.m_Object;
                case LT:
                    return *(double *)m_Object < *(double *) other.m_Object;
                case GEQ:
                    return *(double *)m_Object >= *(double *) other.m_Object;
                case LEQ:
                    return *(double *)m_Object <= *(double *) other.m_Object;
            }
        }
        case CONDITION: {
            switch (comparison) {
                case EQ:
                    return (*(Condition *)m_Object).evaluate() == (*(Condition *)other.m_Object).evaluate();
                case NEQ:
                    return (*(Condition *)m_Object).evaluate() != (*(Condition*)other.m_Object).evaluate();
                default:
                    return false;
            }
        }
    }
}