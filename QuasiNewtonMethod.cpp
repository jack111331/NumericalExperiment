//
// Created by Edge on 2020/7/12.
//

#include "QuasiNewtonMethod.h"
#include <vector>
#include <iostream>

using namespace std;

vector<float> QuasiNewtonMethod::optimize(const vector<float> &x0, float epsilon, DerivativeVector *derivative) {
    int dim = x0.size();
    vector<vector<float>> approximateHessianMatrix;
    vector<vector<float>> inverseHessianMatrix;
    vector<float> x(x0);

    const float alpha = 0.25f, beta = 0.8f;

    for (int i = 0; i < dim; ++i) {
        vector<float> rowEntry;
        for (int j = 0; j < dim; ++j) {
            if (i == j) {
                rowEntry.push_back(1.0f);
            } else {
                rowEntry.push_back(0.0f);
            }
        }
        approximateHessianMatrix.push_back(rowEntry);
        inverseHessianMatrix.push_back(rowEntry);
    }

    float error = 1e10;
    int it = 0;
    while (error > epsilon) {
        cout << "Iteration: " << ++it << endl;
        fflush(stdout);
        vector<float> direction;
        vector<float> gradient = derivative->getDerivative(x);
        float gradientProduct = 0.0f;
        for (int i = 0; i < x.size(); ++i) {
            direction.push_back(0.0f);
            for (int j = 0; j < x.size(); ++j) {
                direction[i] += inverseHessianMatrix[i][j] * -gradient[j];
            }
            gradientProduct += gradient[i] * gradient[i];
        }

        // here use basic newton line search

        vector<float> sk;
        float step = 1.0f;
        vector<float> trialNewX;
        for(int i = 0;i < x.size();++i) {
            trialNewX.push_back(x[i] + step * direction[i]);
        }
        float currentFunctionValue = derivative->getFunctionValue(x);
        while(derivative->getFunctionValue(trialNewX) > currentFunctionValue - alpha * step * gradientProduct) {
            step *= beta;
            for(int i = 0;i < x.size();++i) {
                trialNewX[i] = x[i] + step * direction[i];
            }
            cout << derivative->getFunctionValue(trialNewX) << " " << currentFunctionValue - alpha * step * gradientProduct << " " << step << endl;
        }
        for (int i = 0; i < x.size(); ++i) {
            sk.push_back(step * direction[i]);
        }

        // update x
        for (int i = 0; i < x.size(); ++i) {
            x[i] += sk[i];
        }
        error = currentFunctionValue - derivative->getFunctionValue(x);

        // compute aux
        vector<float> yk = derivative->getDerivative(x);
        for (int i = 0; i < yk.size(); ++i) {
            yk[i] -= direction[i];
        }

        // update approximate hessian matrix
        vector<vector<float>> ykykTWithDenomProduct;
        vector<float> bkskProduct;
        vector<vector<float>> bkskskTProduct;
        vector<vector<float>> bkskskTbkTProductWithDenom;
        for (int i = 0; i < x.size(); ++i) {
            vector<float> rowEntry;
            for (int j = 0; j < x.size(); ++j) {
                rowEntry.push_back(0.0f);
            }
            ykykTWithDenomProduct.push_back(rowEntry);
            bkskProduct.push_back(0.0f);
            bkskskTProduct.push_back(rowEntry);
            bkskskTbkTProductWithDenom.push_back(rowEntry);
        }

        float ykskDot = 0.0f;
        for (int i = 0; i < x.size(); ++i) {
            ykskDot += yk[i] * sk[i];
        }
        for (int i = 0; i < x.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                ykykTWithDenomProduct[i][j] = yk[i] * yk[j] / ykskDot;
            }
        }

        // compute left
        for (int i = 0; i < x.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                bkskProduct[i] += approximateHessianMatrix[i][j] * sk[j];
            }
        }

        // compute center
        for (int i = 0; i < x.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                bkskskTProduct[i][j] = bkskProduct[i] * sk[j];
            }
        }

        // compute right
        float skTbksk = 0.0f;
        for (int i = 0; i < x.size(); ++i) {
            skTbksk += sk[i] * bkskProduct[i];
        }
        for (int i = 0; i < x.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                for (int k = 0; k < x.size(); ++k) {
                    bkskskTbkTProductWithDenom[i][j] += bkskskTProduct[i][k] * approximateHessianMatrix[j][k];
                }
                bkskskTbkTProductWithDenom[i][j] /= skTbksk;
            }
        }

        for (int i = 0; i < x.size(); ++i) {
            for (int j = 0; j < x.size(); ++j) {
                approximateHessianMatrix[i][j] += ykykTWithDenomProduct[i][j] - bkskskTbkTProductWithDenom[i][j];
            }
        }

        vector<vector<float>> skskTWithDenom;
        float skTyk = 0.0f;
        for (int i = 0; i < x.size(); ++i) {
            skTyk += sk[i] * yk[i];
        }
        vector<float> ykTbkI;
        for (int i = 0; i < x.size(); ++i) {
            ykTbkI.push_back(0.0f);
            for (int j = 0; j < x.size(); ++j) {
                ykTbkI[i] += yk[j] * inverseHessianMatrix[j][i];
            }
        }

        float ykTbkIyk = 0.0f;
        for (int i = 0; i < x.size(); ++i) {
            ykTbkIyk += ykTbkI[i] * yk[i];
        }

        float secondTermLeftFactor = (skTyk + ykTbkIyk) / skTyk / skTyk;
        for (int i = 0; i < x.size(); ++i) {
            vector<float> rowEntry;
            for (int j = 0; j < x.size(); ++j) {
                rowEntry.push_back(secondTermLeftFactor * sk[i] * sk[j]);
            }
            skskTWithDenom.push_back(rowEntry);
        }

        vector<float> bkIyk;
        for (int i = 0; i < x.size(); ++i) {
            bkIyk.push_back(0.0f);
            for(int j = 0;j < x.size();++j) {
                bkIyk[i] += inverseHessianMatrix[i][j] * yk[j];
            }
        }

        vector<vector<float>> bkIykskT;
        for (int i = 0; i < x.size(); ++i) {
            vector<float> rowEntry;
            for(int j = 0;j < x.size();++j) {
                rowEntry.push_back(bkIyk[i] * sk[j]);
            }
            bkIykskT.push_back(rowEntry);
        }

        vector<vector<float>> skykT;
        for (int i = 0; i < x.size(); ++i) {
            vector<float> rowEntry;
            for(int j = 0;j < x.size();++j) {
                rowEntry.push_back(sk[i] * yk[j]);
            }
            skykT.push_back(rowEntry);
        }

        vector<vector<float>> skykTbkI;
        for (int i = 0; i < x.size(); ++i) {
            vector<float> rowEntry;
            for(int j = 0;j < x.size();++j) {
                rowEntry.push_back(0.0f);
                for(int k = 0;k < x.size();++k) {
                    rowEntry[j] += skykT[i][k] * inverseHessianMatrix[k][j];
                }
            }
            skykTbkI.push_back(rowEntry);
        }

        vector<vector<float>> thirdTermWithDenom;
        for(int i = 0;i < x.size();++i) {
            vector<float> rowEntry;
            for(int j = 0;j < x.size();++j) {
                rowEntry.push_back((skskTWithDenom[i][j] + skykTbkI[i][j]) / skTyk);
            }
            thirdTermWithDenom.push_back(rowEntry);
        }

        for(int i = 0;i < x.size();++i) {
            for(int j = 0;j < x.size();++j) {
                inverseHessianMatrix[i][j] += skskTWithDenom[i][j] - thirdTermWithDenom[i][j];
            }
        }
    }
    return x;
}