//
// Created by Edge on 2020/7/8.
//

#include "MidpointMethod.h"

float MidpointMethod::ivp(float x0, float y0, float dt, float x1, Derivative *derivative) {
    while (x0 < x1) {
        // Reference: https://graphics.stanford.edu/courses/cs448b-00-winter/papers/phys_model.pdf
        y0 += dt * (derivative->getDerivative(x0 + dt * 0.5 * (derivative->getDerivative(x0))));
        x0 += dt;
    }
    return y0;
}