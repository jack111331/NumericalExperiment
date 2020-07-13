//
// Created by Edge on 2020/7/12.
//

#include "ObjectiveFunctionOne.h"
#include <vector>

std::string ObjectiveFunctionOne::getFunctionInfo() const {
    return "f(x) = 5x_1^2 - 9 * x_1 *x_2 + 4.075x_2^2 + x_1\n";
}

float ObjectiveFunctionOne::getFunctionValue(const std::vector<float> &x) const {
    return 5*x[0]*x[0] - 9*x[0]*x[1] + 4.075*x[1]*x[1] + x[0];
}

std::vector<float> ObjectiveFunctionOne::getDerivative(const std::vector<float> &x) const {
    std::vector<float> derivativeList;
    derivativeList.push_back(10.0f * x[0] - 9.0f * x[1] + 1.0f);
    derivativeList.push_back(-9.0f*x[0] + 8.15f*x[1]);
    return derivativeList;
}