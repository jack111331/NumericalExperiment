//
// Created by Edge on 2020/7/8.
//

#include "FunctionOne.h"

std::string FunctionOne::getFunctionInfo() const {
    return "f(x) = x^2\nf'(x) = 2x\n";
}

float FunctionOne::getDerivative(float x) {
    return 2 * x;
}