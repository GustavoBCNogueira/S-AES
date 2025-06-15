CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iheaders
SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = main
MAIN_SRC = main.cpp

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS) $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lssl -lcrypto

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean