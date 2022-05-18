TARGET = square

CXX = g++ 
CFLAGS = -Wall -O3 
CXXFLAGS = $(CFLAGS) -std=c++14
INCLUDE =  
LIBS = -lGLEW -lGL -lSDL2


OBJECTS = square.o ../tinyrender.o ../input.o ../window.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(INCLUDE) $(CXXFLAGS) $(OBJECTS) $(LIBS)


square.o : square.cpp ../tinyrender.h


.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)