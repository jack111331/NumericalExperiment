//
// Created by Edge on 2020/7/8.
//

#ifndef NUMERICALEXPERIMENT_EULERMETHOD_H
#define NUMERICALEXPERIMENT_EULERMETHOD_H


#include "Derivative.h"

class EulerMethod {
public:
    float ivp(float x0, float y0, float dt, float x1, Derivative *derivative);
};


#endif //NUMERICALEXPERIMENT_EULERMETHOD_H
