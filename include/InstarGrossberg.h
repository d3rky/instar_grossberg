#ifndef INSTAR_GROSSBERG_H

#define INSTAR_GROSSBERG_H

#include <vector>

#include "Neuron.h"

namespace neuron {
    
class InstarGrossberg: public Neuron {
    public:
        /**
         * @constructor
         */
        InstarGrossberg(const int inputNum);

    protected:

        /**
         * Евклидова норма
         *
         * @param {std::vector<double>} вх. вектор
         * 
         * @return {std::vector<double>} нормализованный вектор
         */
        std::vector<double> _normalizeInput(std::vector<double> input);

        /**
         * Функция активации нейрона
         *
         * @param {double} вх. взвешенная сумма
         *
         * @return double
         */
        virtual double _activationFunc(double input);
};

}; //namespace neuron

#endif
