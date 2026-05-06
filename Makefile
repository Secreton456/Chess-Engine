PYTHON := python3
EXT := $(shell $(PYTHON) -m pybind11 --extension-suffix)
INCLUDES := $(shell $(PYTHON) -m pybind11 --includes)

CXX := c++
CXXFLAGS := -O3 -Wall -shared -std=c++17 -fPIC \
$(INCLUDES) \
-Ibackend/include

TARGET := frontend/board$(EXT)
SRC := backend/src/board.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f frontend/board*.so frontend/board*.pyd