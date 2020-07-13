//
// Created by Edge on 2020/7/8.
//

#ifndef NUMERICALEXPERIMENT_MIDPOINTMETHOD_H
#define NUMERICALEXPERIMENT_MIDPOINTMETHOD_H

#include "Derivative.h"

class MidpointMethod {
public:
    float ivp(float x0, float y0, float dt, float x1, Derivative *derivative);
};


#endif //NUMERICALEXPERIMENT_MIDPOINTMETHOD_H
