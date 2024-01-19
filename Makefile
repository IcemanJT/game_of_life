CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/gof

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

# Dependencies
$(OBJ_DIR)/GameOfLife.o: $(SRC_DIR)/GameOfLife.cpp $(SRC_DIR)/GameOfLife.hpp $(SRC_DIR)/CursorList.hpp
$(OBJ_DIR)/CursorList.o: $(SRC_DIR)/CursorList.cpp $(SRC_DIR)/CursorList.hpp

# Include dependencies
-include $(OBJ_FILES:.o=.d)

# Generate dependencies
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -MM -MT '$(OBJ_DIR)/$*.o' $< -MF $@
