#ifndef INSTAR_GROSSBERG_TRAINER_H

#define INSTAR_GROSSBERG_TRAINER_H

#include "Trainer.h"

namespace trainer {

class InstarGrossbergTrainer: public Trainer {
    
    public:
        
        /**
         * @constructor
         */
        InstarGrossbergTrainer(const double nu, const double eps, const int cycleNum);

        /**
         * Обучение с учителем
         *
         * @param {neuron::Neuron*} нейрон, который надо обучить
         * @param {char*} путь до файлика с обучающими данными
         *
         * @return {neuron::Neuron*} обученный нейрон
         */
        virtual neuron::Neuron* trainWithTeacher(
            neuron::Neuron* na,
            char* path
        );

        /**
         * Обучение без учителя
         *
         * @param {neuron::Neuron*} нейрон, который надо обучить
         * @param {char*} путь до файли с обучающими данными
         *
         * @return {neuron::Neuron*} обученный нейрон
         */
        virtual neuron::Neuron* trainAlone(
            neuron::Neuron* na,
            char* path
        );

    private:
        /**
         * Количество циклов обучания
         */
        const int _cycleNum;
};

}; //namespace trainer

#endif
