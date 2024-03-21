LIB_NAME=common
BUILD_DIR=build
TARGET=$(BUILD_DIR)/lib$(LIB_NAME).a
SRC= $(wildcard *.cpp)
OBJECTS=$(patsubst %, $(BUILD_DIR)/%, $(SRC:.cpp=.o))

ifeq ($(ARCH), aarch64)
	CC=aarch64-linux-gnu-g++
	AR=aarch64-linux-gnu-ar
else
	CC=g++
	AR=ar
endif

CC_FLAGS=-Wall
LD_FLAGS=rcs
REMOVE=rm -fdr

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(AR) $(LD_FLAGS) $(TARGET) $(OBJECTS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR) 

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -o $@ -c $< $(CC_FLAGS)

clean:
	$(REMOVE) $(BUILD_DIR) $(TARGET) *.o
