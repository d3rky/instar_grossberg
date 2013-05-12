CC=g++
CFLAGS=-c -Wall

SOURCE_DIR=src
BUILD_DIR=build

#define .cpp for modules
NEURON_CPP=$(SOURCE_DIR)/neurons/Neuron.cpp $(SOURCE_DIR)/neurons/InstarGrossberg.cpp

TRAINER_CPP=$(SOURCE_DIR)/trainers/Trainer.cpp $(SOURCE_DIR)/trainers/InstarGrossbergTrainer.cpp

UTILS_CPP=$(SOURCE_DIR)/DataReader.cpp

MAIN_CPP=$(SOURCE_DIR)/main.cpp

SOURCES=$(NEURON_CPP) $(MAIN_CPP) $(UTILS_CPP) $(TRAINER_CPP)
OBJECTS=$(SOURCES:.cpp=.o)

all: neuron

neuron: object_dir $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BUILD_DIR)/neuron
	rm -rf $(SOURCE_DIR)/**/*.o

object_dir:
	mkdir -p build

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(SOURCE_DIR)/**/*.o $(BUILD_DIR)/neuron
