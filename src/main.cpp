#include <iostream>
#include <vector>

#include "../include/InstarGrossberg.h" 
#include "../include/InstarGrossbergTrainer.h"

int main(int argc, char** argv) {

    //количество входов нейрона
    const int inputsNum = 2;
    //количество циклов обучения
    const int cycleNum = 10;

    neuron::Neuron* na = new neuron::InstarGrossberg(inputsNum);

    trainer::Trainer* train = new trainer::InstarGrossbergTrainer(0.35, 1E-4, cycleNum);

    na = train->trainWithTeacher(na, "build/test.input");

}
