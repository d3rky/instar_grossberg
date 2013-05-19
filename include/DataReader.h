#ifndef DATA_READER_H

#define DATA_READER_H

#include <vector>
#include <fstream>

/**
 * @class считываем тестовые данные с файла
 */
class DataReader {
    
    public:
        /**
         * @constructor
         */
        DataReader();

        ~DataReader();

        /**
         * Прочитать тестовые данные из файла
         *
         * @param {char*} путь до тестового файла
         */
        std::vector<std::vector<double> > readTestFile(
            char* path
        );


    protected:
        std::ifstream _inputStream;
};

#endif
