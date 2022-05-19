TARGET = main
TARGET_OBJ = $(TARGET).o

CXX = g++

CXXFLAGS = -O3 -march=native -std=c++2a -Wall -Wfatal-errors
CXXLIBS = -L/usr/local/cuda/lib64 -lcuda -lcudart -ltbb -pthread \
	./dependencies/glad/lib/libglad.a -lglfw -lX11 -lpthread -lXrandr -lXi -ldl \


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
main.o: $(CXX_OBJECTS) shader.h window.h event.h camera.h render.h objects.h

#explicit dependencies
#$(OBJ_FOLDER)/distance.o: $(OBJ_FOLDER)/primitives.o

clean:
	rm -rf $(CXX_OBJECTS) $(TARGET) $(TARGET_OBJ) $(TARGET_LIB)




# T * R * S
# V_clip = M_proj * M_view * M_model * V_local

# M_model = transform into world coord
# M_view = camera of OpenGL (camera's point of view)
# M_proj = transforn vertex coord into clip space range(-1000,1000) -> (-1,1)