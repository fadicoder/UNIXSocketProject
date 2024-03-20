APPLICATION_NAME=server
BUILD_DIR=build
TARGET=$(BUILD_DIR)/$(APPLICATION_NAME)
SRC= $(wildcard *.cpp)
OBJECTS=$(patsubst %, $(BUILD_DIR)/%, $(SRC:.cpp=.o))

CC=g++
INCLUDE_PATH=../lib
LIB_PATH=$(INCLUDE_PATH)/build/lib.a
REMOVE=rm -fdr

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) -L. $(LIB_PATH)

$(BUILD_DIR):
	mkdir $(BUILD_DIR) 

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -I $(INCLUDE_PATH) -o $@ -c $<

clean:
	$(REMOVE) $(TARGET) $(BUILD_DIR) *.o


run: $(TARGET)
	./$(TARGET) $(filter-out $@,$(MAKECMDGOALS))

%: # to allow passing arguments
	@exit 0