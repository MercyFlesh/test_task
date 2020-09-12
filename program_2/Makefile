CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -lpthread -lstdc++
SOURCES = main.cpp Server.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = program_2

.PHONY: all clean

all: $(TARGET)

clean:
		rm -rf $(OBJECTS)
	
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@