//
// Created by Edge on 2020/7/8.
//

#include "EulerMethod.h"

float EulerMethod::ivp(float x0, float y0, float dt, float x1, Derivative *derivative) {
    while(x0 < x1) {
        y0 += derivative->getDerivative(x0);
        x0 += dt;
    }
    return y0;
}