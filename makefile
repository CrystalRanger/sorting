CC := gcc
CXX := g++

FINAL_EXEC := sorter
BUILD_PATH := ./build

SRC_PATH := ./src


INC_PATHS := ./include /usr/local/include
INC_FLAGS := $(addprefix -I,$(INC_PATHS))

LIB_PATHS := /usr/local/lib
LIB_FLAGS := $(addprefix -L,$(LIB_PATHS))

LIBS := raylib
LIBS_FLAGS := $(addprefix -l,$(LIBS))

CFLAGS = -Wall $(INC_FLAGS) $(LIB_FLAGS) $(LIBS_FLAGS) -std=c++11

SOURCES := $(wildcard $(SRC_PATH)/*.c $(SRC_PATH)/*.cpp)
OBJECTS := $(SOURCES:%=%.o)


.PHONY := clean run test

$(BUILD_PATH)/$(FINAL_EXEC): $(OBJECTS)
	@$(CXX) $(CFLAGS) -o $@ $<
	@echo "Linking $<"

$(SRC_PATH)/%.cpp.o: $(SRC_PATH)/%.cpp
	@$(CXX) $(CFLAGS) -c -o $@ $<
	@echo "Compiling $<"

clean:
	rm $(SRC_PATH)/*.o

run: $(BUILD_PATH)/$(FINAL_EXEC)
	@./$(BUILD_PATH)/$(FINAL_EXEC)