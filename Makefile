PYTHON := python3
EXT := $(shell $(PYTHON) -m pybind11 --extension-suffix)
INCLUDES := $(shell $(PYTHON) -m pybind11 --includes)

TARGET := game$(EXT)

all: $(TARGET)

$(TARGET): game.cpp
	c++ -O3 -Wall -shared -std=c++17 -fPIC $(INCLUDES) $< -o $@