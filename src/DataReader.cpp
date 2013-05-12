#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/DataReader.h"

////////////////////////////////////////////////////////////////////////////////
// constructors

DataReader::DataReader() {
    ;
};

DataReader::~DataReader() {
    if(_inputStream.is_open()) {
        _inputStream.close();
    }
}

////////////////////////////////////////////////////////////////////////////////
// public functions

std::vector<std::vector<double> > DataReader::readTestFile(
    char* path
) {
    if(_inputStream.is_open()) {
        _inputStream.close();
    }
    _inputStream.open(path, std::ifstream::in);

    std::vector<std::vector<double> > result;
    std::string line;

    if(_inputStream.is_open()) {
        while(std::getline(_inputStream, line)) {
            std::stringstream inStringStream(line);
            double number;
            std::vector<double> batchNumber;

            while(inStringStream >> number) {
                batchNumber.push_back(number);
            }

            result.push_back(batchNumber);
        }
    }

    return result;
};
