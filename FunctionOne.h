//
// Created by Edge on 2020/7/8.
//

#ifndef NUMERICALEXPERIMENT_FUNCTIONONE_H
#define NUMERICALEXPERIMENT_FUNCTIONONE_H


#include "Derivative.h"

class FunctionOne : public Derivative {
public:
    virtual std::string getFunctionInfo() const;

    virtual float getDerivative(float x);
};


#endif //NUMERICALEXPERIMENT_FUNCTIONONE_H
