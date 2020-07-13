//
// Created by Edge on 2020/7/12.
//

#ifndef NUMERICALEXPERIMENT_OBJECTIVEFUNCTIONONE_H
#define NUMERICALEXPERIMENT_OBJECTIVEFUNCTIONONE_H


#include "Derivative.h"

class ObjectiveFunctionOne : public DerivativeVector {
public:
    virtual std::string getFunctionInfo() const;

    virtual float getFunctionValue(const std::vector<float> &x) const;

    virtual std::vector<float> getDerivative(const std::vector<float> &x) const;
};


#endif //NUMERICALEXPERIMENT_OBJECTIVEFUNCTIONONE_H
