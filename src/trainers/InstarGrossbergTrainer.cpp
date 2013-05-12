#include <cmath>

#include "../../include/InstarGrossbergTrainer.h"

using namespace trainer;

////////////////////////////////////////////////////////////////////////////////
// constructors

InstarGrossbergTrainer::InstarGrossbergTrainer(
    const double nu,
    const double eps,
    const int cycleNum
) : Trainer(nu, eps), _cycleNum(cycleNum) {
    ;
};


////////////////////////////////////////////////////////////////////////////////
// public functions

neuron::Neuron* InstarGrossbergTrainer::trainWithTeacher(
    neuron::Neuron* na,
    char* path
) {
    std::vector<std::vector<double> > trainingCouples = _reader->readTestFile(path);
    std::vector<std::vector<double> >::iterator couples_iter = trainingCouples.begin();

    //Выставляем значения весов в 0
    na->setWeightsToZero();
    std::vector<double> w = na->getWeights();

    for(int i=0; i<_cycleNum; i++) {
        for(; couples_iter != trainingCouples.end(); ++couples_iter) {
            double d = (*couples_iter).back();
            double norm = _getVectorNorm(*couples_iter);

            for(int j=0; j<w.size(); j++) {
                double increment = _nu*d*((*couples_iter)[j]/norm-w[j]);

                w[j] = w[j] + increment;
            }
        }
    }

    na->setWeights(w);

    return na;
};


neuron::Neuron* InstarGrossbergTrainer::trainAlone(
    neuron::Neuron* na,
    char* path
) {
    std::vector<std::vector<double> > trainingCouples = _reader->readTestFile(path);
    std::vector<std::vector<double> >::iterator couples_iter = trainingCouples.begin();

    //Выставляем рандомное значение весов
    na->setRandomWeights();
    std::vector<double> w = na->getWeights();

    for(; couples_iter != trainingCouples.end(); ++couples_iter) {
        (*couples_iter).pop_back();

        std::vector<double> input = (*couples_iter);
        double y = na->getOutput(input);

        
        for(int i=0; i<w.size(); i++) {
            double increment = _nu*y*((*couples_iter)[i]-w[i]);
            int iterations = 0;

            while(fabs(increment) >= _eps or iterations < _maxIterations) {
                w[i] = w[i] + increment;

                increment = _nu*y*((*couples_iter)[i]-w[i]);
                iterations += 1;

                na->setWeights(w);

                y = na->getOutput(input);
            }
        }

        na->setWeights(w);
    }

    return na;
}
