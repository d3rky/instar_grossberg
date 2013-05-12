#ifndef TRAINER_H

#define TRAINER_H

#include <vector>

#include "Neuron.h"
#include "DataReader.h"

namespace trainer {

/**
 * @class класс для обучения нейрона
 */
class Trainer {

    public:

        /**
         * @constructor
         *
         * @param {const double} коэффициент обучения
         * @param {const double} точность решения
         */
        Trainer(const double nu, const double eps);
    
        virtual neuron::Neuron* trainWithTeacher(
            neuron::Neuron* na, 
            char* path
        ) = 0;

        virtual neuron::Neuron* trainAlone(
            neuron::Neuron* na, 
            char* path
        ) = 0;  

        virtual ~Trainer() {};

    protected:

        /**
         * Коэффициент обучения
         */
        const double _nu;

        /**
         * точность решения
         */
        const double _eps;

        /**
         * макс. количество итераций для одного нейрона с одной обучающей парой
         */
        static const int _maxIterations = 1000;

        /**
         * datareader
         */
        DataReader* _reader;

        /**
         * Нормализуем набор данных по одному из измерений
         *
         * @param {vector<vector<double> >} входные данные
         * @param {const int} номер измерения, начиная с 1
         *
         * @return {vector<vector<double> >} нормализованные данные по
         *      переданному измерению
         */
        std::vector<std::vector<double> > _normalizeData(
            std::vector<std::vector<double> > inputData,
            const int dimension
        );

        /**
         * Нормализуем дабор данных по всем измерениям
         *
         * @param входные данные
         *
         * @return нормализованные данные по
         *      переданному измерению
         */
        double _getVectorNorm(
            std::vector<double> vec
        );

};

}; //trainer namespace

#endif
