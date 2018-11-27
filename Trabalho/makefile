BIN_NAME = main

CXX = g++

CXXFLAGS = -O3 -Wall -Wextra -fopenmp -std=c++11 -Wno-unused-parameter -L/share/apps/papi/5.5.0/lib -I/share/apps/papi/5.5.0/include -lpapi -fopt-info-missed=results/vectorization.txt
#CXXFLAGS    = -O3 -Wall -Wextra -qopenmp -std=c++11 -Wno-unused-parameter -qopt-report=3

SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build
LOG_DIR = logs
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst src/%.cpp,build/%.o,$(SRC))
DEPS = $(patsubst build/%.o,build/%.d,$(OBJ))
BIN = $(BIN_NAME)

vpath %.cpp $(SRC_DIR)

.DEFAULT_GOAL = all

$(BUILD_DIR)/%.d: %.cpp
	$(CXX) -M $< -o $@ -lm $(CXXFLAGS)

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) -c $< -o $@ -lm $(CXXFLAGS)

$(BIN_DIR)/$(BIN_NAME): $(DEPS) $(OBJ)
	$(CXX) -o $@ $(OBJ) -lm $(CXXFLAGS)

checkdirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

all: checkdirs $(BIN_DIR)/$(BIN_NAME)

clean:
	rm -f $(BUILD_DIR)/* $(BIN_DIR)/*
