#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

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
    std::cout<<"y(x,a)=a*x;"<<std::endl;
    std::cout<<"set size ratio 1;"<<std::endl;
    std::cout<<"set xrange [-1:1]; set yrange[-1:1]"<<std::endl;

    std::vector<std::vector<double> > trainingCouples = _reader->readTestFile(path);

    //std::cout<<"plot \"./build/test.input\" using 1:2 with points;"<<std::endl;

    //Выставляем значения весов в 0
    na->setWeightsToZero();
    std::vector<double> w = na->getWeights();
    
    w[0] = -1;
    w[1] = 0;

    std::ofstream init_stream("build/weights_init.output");
    init_stream << "0.0 0.0"<<std::endl<<w[0]<<" "<<w[1]<<std::endl;

    std::cout<<"plot \"./build/test.input\" with points, \"./build/weights_init.output\" with lines;"<<std::endl;
    std::cout<<"pause 1.0;"<<std::endl;

    for(int i=0; i<_cycleNum; i++) {
       std::vector<std::vector<double> >::iterator couples_iter = trainingCouples.begin();

       for(int c_i=0; couples_iter != trainingCouples.end(); ++couples_iter, c_i++) {
            std::stringstream filename;
            filename << "build/weights"<<i<<"_"<<c_i<<".output";
            const std::string tmp = filename.str();

            std::ofstream stream(tmp.c_str()); 
            double d = (*couples_iter).back();
            double norm = _getVectorNorm(*couples_iter);

            for(int j=0; j<w.size(); j++) {
                double increment = _nu*d*((*couples_iter)[j]/norm-w[j]);

                w[j] = w[j] + increment;
            }

            double wNorm = _getVectorNorm(w);
            for(int j=0; j<w.size(); j++) {
               w[j] = w[j] / wNorm;
            }

            stream << "0.0 0.0"<<std::endl;
            stream<<w[0]<<" "<<w[1]<<std::endl;
            stream.close();

            std::cout<<"plot \"./build/test.input\" with points, \"./"<<filename.str()<<"\" with lines;"<<std::endl;
            std::cout<<"pause 0.1;"<<std::endl;
        }
        _nu = _nu - 0.03;
    }

   std::cout<<"pause 500;"<<std::endl;

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
