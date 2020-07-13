//
// Created by Edge on 2020/7/12.
//

#ifndef NUMERICALEXPERIMENT_QUASINEWTONMETHOD_H
#define NUMERICALEXPERIMENT_QUASINEWTONMETHOD_H

#include <vector>
#include "Derivative.h"

class QuasiNewtonMethod {
public:
    std::vector<float> optimize(const std::vector<float> &x0, float epsilon, DerivativeVector *derivative);
};


#endif //NUMERICALEXPERIMENT_QUASINEWTONMETHOD_H
