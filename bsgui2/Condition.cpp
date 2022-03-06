//
// Created by Saar Keynan on 02/03/2022.
//

#include "Condition.h"
#include "ConditionObject.h"

bool Condition::evaluate() {
    return m_FirstCond->evaluate(*m_SecondCond, m_Comparison);
}