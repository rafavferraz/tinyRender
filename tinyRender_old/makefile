TARGET = main

CXX = g++ 
CFLAGS = -Wall -O3 
CXXFLAGS = $(CFLAGS) -std=c++14
INCLUDE =  
LIBS = -lGLEW -lGL -lSDL2


OBJECTS = main.o tinyrender.o input.o camera.o render.o buffer.o window.o

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(INCLUDE) $(CXXFLAGS) $(OBJECTS) $(LIBS)


main.o : main.cpp tinyrender.h

tinyrender.o : tinyrender.h input.h camera.h render.h buffer.h window.h
input.o : input.h keymap.h camera.h
camera.o : camera.h
render.o : buffer.h render.h 
buffer.o : buffer.h 
window.o : window.h



# $(OBJECTS) : ../genetics.h \
# 			 ../population.h \
# 			 ../transcription.h \
# 			 ../fitness.h \
# 			 ../search_operators.h \
# 			 ../selection.h \
# 			 ../run.h


.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)