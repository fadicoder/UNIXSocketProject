LIB_NAME=common
BUILD_DIR=build
TARGET=$(BUILD_DIR)/lib$(LIB_NAME).a
SRC= $(wildcard *.cpp)
OBJECTS=$(patsubst %, $(BUILD_DIR)/%, $(SRC:.cpp=.o))

CC=g++
CC_FLAGS=-Wall
AR=ar rcs
REMOVE=rm -fdr

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(AR) $(TARGET) $(OBJECTS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR) 

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -o $@ -c $< $(CC_FLAGS)

clean:
	$(REMOVE) $(BUILD_DIR) $(TARGET) *.o
