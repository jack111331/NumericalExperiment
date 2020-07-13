#include <iostream>
#include "EulerMethod.h"
#include "FunctionOne.h"
#include "MidpointMethod.h"
#include "ObjectiveFunctionOne.h"
#include "QuasiNewtonMethod.h"

using namespace std;

static void ivp() {
    EulerMethod *eulerMethod = new EulerMethod();
    MidpointMethod *midpointMethod = new MidpointMethod();
    FunctionOne *functionOne = new FunctionOne();
    cout << "Function 1:\n" << functionOne->getFunctionInfo() << endl;

    float x0 = 0, y0 = 5, dt = 0.02, x1 = 10;
    cout << "Given x0 = " << x0 << "\ny0 = " << y0 << "\ndt = " << dt << "\nx1 = " << x1 << endl;
    cout << "Euler Method result: " << eulerMethod->ivp(x0, y0, dt, x1, functionOne) << endl;

    cout << "Midpoint Method result: " << midpointMethod->ivp(x0, y0, dt, x1, functionOne) << endl;
    delete eulerMethod;
    delete midpointMethod;
    delete functionOne;
}

static void optimization() {
    QuasiNewtonMethod *quasiNewtonMethod = new QuasiNewtonMethod();
    ObjectiveFunctionOne *objectiveFunctionOne = new ObjectiveFunctionOne();
    cout << "Objective Function 1:\n" << objectiveFunctionOne->getFunctionInfo() << endl;

    vector<float> x0;
    x0.push_back(0.0f);
    x0.push_back(0.0f);
    float epsilon = 3e-7;
    cout << "Given x0 = [" << x0[0] << ", " << x0[1] << "]" << std::endl;
    vector<float> x = quasiNewtonMethod->optimize(x0, epsilon, objectiveFunctionOne);
    cout << "After Quasi Newton optimization, the result x=[" << x[0] << ", " << x[1] << "]" << std::endl;
}

int main() {
    ivp();
    optimization();
    return 0;
}
