APPLICATION_NAME=client
BUILD_DIR=build
TARGET=$(BUILD_DIR)/$(APPLICATION_NAME)
SRC= $(wildcard *.cpp)
OBJECTS=$(patsubst %, $(BUILD_DIR)/%, $(SRC:.cpp=.o))

CC=g++
REMOVE=rm -fdr

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR) 

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	$(REMOVE) $(TARGET) $(BUILD_DIR) *.o


run: $(TARGET)
	./$(TARGET) $(filter-out $@,$(MAKECMDGOALS))

%: # to allow passing arguments
	@exit 0