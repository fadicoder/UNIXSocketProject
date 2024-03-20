LIB_NAME=lib
BUILD_DIR=build
TARGET=$(BUILD_DIR)/$(LIB_NAME).a
SRC= $(wildcard *.cpp)
OBJECTS=$(patsubst %, $(BUILD_DIR)/%, $(SRC:.cpp=.o))

CC=g++
AR=ar rcs
REMOVE=rm -fdr

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(AR) $(TARGET) $(OBJECTS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR) 

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	$(REMOVE) $(BUILD_DIR) $(TARGET) *.o
