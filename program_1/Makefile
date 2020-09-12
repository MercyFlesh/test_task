CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -lpthread -lstdc++
SOURCES = main.cpp ProducerConsumer.cpp Client.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = program_1

.PHONY: all clean

all: $(TARGET)

clean:
		rm -rf $(OBJECTS)
	
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@