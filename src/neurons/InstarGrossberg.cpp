#include <vector>
#include <math.h>

#include "../../include/InstarGrossberg.h"

using namespace neuron;

////////////////////////////////////////////////////////////////////////////////
// constructors

InstarGrossberg::InstarGrossberg(const int inputNum)
: Neuron(inputNum) {
    ;
};

////////////////////////////////////////////////////////////////////////////////
// private functions

std::vector<double> InstarGrossberg::_normalizeInput(std::vector<double> input) {
    std::vector<double> normalized;
    std::vector<double>::iterator iter = input.begin();
    double sum = 0.0,
            norma;

    for(; iter != input.end(); ++iter) {
        sum += pow(*iter, 2);
    }

    norma = sqrt(sum);

    for(iter=input.begin(); iter != input.end(); ++iter) {
        normalized.push_back(*(iter)/norma);
    }

    return normalized;
};


double InstarGrossberg::_activationFunc(double input) {
    return input;
};
