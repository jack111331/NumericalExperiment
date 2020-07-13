//
// Created by Edge on 2020/7/8.
//

#ifndef NUMERICALEXPERIMENT_DERIVATIVE_H
#define NUMERICALEXPERIMENT_DERIVATIVE_H

#include <string>
#include <vector>

class Derivative {
public:
    virtual std::string getFunctionInfo() const = 0;
    virtual float getDerivative(float x) = 0;
};

class DerivativeVector {
public:
    virtual std::string getFunctionInfo() const = 0;
    virtual float getFunctionValue(const std::vector<float> &x) const = 0;
    virtual std::vector<float> getDerivative(const std::vector<float> &x) const = 0;
};


#endif //NUMERICALEXPERIMENT_DERIVATIVE_H
