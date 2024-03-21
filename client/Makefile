APPLICATION_NAME=client
BUILD_DIR=build
TARGET=$(BUILD_DIR)/$(APPLICATION_NAME)
SRC= $(wildcard *.cpp)
OBJECTS=$(patsubst %, $(BUILD_DIR)/%, $(SRC:.cpp=.o))

ifeq ($(ARCH), aarch64)
	CC=aarch64-linux-gnu-g++
else
	CC=g++
endif

INCLUDE_PATH=../lib
LIB_PATH=$(INCLUDE_PATH)/build/lib.a
LD_FLAGS= -L../lib/build -lcommon
CC_FLAG=-Wall -I $(INCLUDE_PATH)

REMOVE=rm -fdr

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LD_FLAGS) 

$(BUILD_DIR):
	mkdir $(BUILD_DIR) 

$(BUILD_DIR)/%.o: %.cpp
	$(CC) -l. -o $@ -c $< $(CC_FLAG)

clean:
	$(REMOVE) $(TARGET) $(BUILD_DIR) *.o
