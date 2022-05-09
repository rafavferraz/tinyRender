TARGET = main
TARGET_OBJ = $(TARGET).o

CXX = g++

CXXFLAGS = -O3 -march=native -std=c++2a -Wall -Wfatal-errors
CXXLIBS = -L/usr/local/cuda/lib64 -lcuda -lcudart -ltbb -pthread \
-lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl


INC_FOLDER = ./include
SRC_FOLDER = ./src
OBJ_FOLDER = ./obj

CXX_OBJECTS = #$(OBJ_FOLDER)/primitives.o \

#compile, but into different folder
$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp $(INC_FOLDER)/%.h
	$(CXX) -c $(CXXFLAGS) -o $@ $<

#link
$(TARGET): $(TARGET_OBJ) $(CXX_OBJECTS) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $(TARGET_OBJ) $(CXX_OBJECTS) $(CXXLIBS) -o $(TARGET) 

#generate static library
$(TARGET_LIB): $(CXX_OBJECTS) 
	ar rcs $@ $^

#dependencies
main.o: $(CXX_OBJECTS) #benchmark.h

#explicit dependencies
#$(OBJ_FOLDER)/distance.o: $(OBJ_FOLDER)/primitives.o

clean:
	rm -rf $(CXX_OBJECTS) $(TARGET) $(TARGET_OBJ) $(TARGET_LIB)






