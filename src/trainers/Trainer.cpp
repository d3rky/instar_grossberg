#include <iostream>
#include <math.h>

#include "../../include/Trainer.h"

using namespace trainer;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// constructors

Trainer::Trainer(const double nu, const double eps)
: _eps(eps) {
    _reader = new DataReader();
    _nu = nu;
};

////////////////////////////////////////////////////////////////////////////////
// private functions

double Trainer::_getVectorNorm(vector<double> vec) {
    vector<double>::iterator iter = vec.begin();

    double sum = 0.0;
    sum = pow(vec[0],2) + pow(vec[1],2);

    return sqrt(sum);
};
