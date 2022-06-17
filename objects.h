#pragma once

#include <numbers>

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Object {

  unsigned int VAO;
  unsigned int VAO_Instanced;

  unsigned int VBO;
  unsigned int VBO_Instanced;
  unsigned int VBO_Instanced_position;

  unsigned int EBO;
  unsigned int EBO_Instanced;

  std::vector<float> vertices;
  std::vector<unsigned int> indexes;

  void load();
  void draw() const;
};

struct Triangle : public Object {

  Triangle() {
    load();
    loadInstanced();  //this make sure vertex_positions in shader is defaulted to vec3(0,0,0) 
                     //necessary if instancedDraw() is not used
  }

  ~Triangle() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
  }

  void load() {

    vertices = {  
     -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f 
    };

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }


  void loadInstanced() {

    static std::vector<glm::vec3> position = { glm::vec3(0.0,0.0,0.0) };
    loadInstanced(position);
  }

  void loadInstanced(const std::vector<glm::vec3>& position) {

    vertices = {  
     -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f 
    };
    
    glGenVertexArrays(1,&VAO_Instanced);
    glGenBuffers(1,&VBO_Instanced);
    glGenBuffers(1,&VBO_Instanced_position);

    glBindVertexArray(VAO_Instanced);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //instance buffer loading
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glBufferData(GL_ARRAY_BUFFER,position.size() * sizeof(glm::vec3), 
      &position[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);	
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
  }

  void draw() const {

    glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
  }

  void drawInstanced(const int& count) const {

    glBindVertexArray(VAO_Instanced);
    glDrawArraysInstanced(GL_TRIANGLES,0,3,count);
    glBindVertexArray(0);
  }
};

struct Square : public Object {

  Square() {
    load();
    loadInstanced();  //this make sure vertex_positions in shader is defaulted to vec3(0,0,0) 
                     //necessary if instancedDraw() is not used
  }

  ~Square() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);
  }

  void load() {

    vertices = {  
      0.5f,  0.5f, 0.0f,  
      0.5f, -0.5f, 0.0f,  
     -0.5f, -0.5f, 0.0f,  
     -0.5f,  0.5f, 0.0f  
    };

    indexes = {
      0, 1, 3,  
      1, 2, 3 
    };

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }

  void loadInstanced() {

    static std::vector<glm::vec3> position = { glm::vec3(0.0,0.0,0.0) };
    loadInstanced(position);
  }

  void loadInstanced(const std::vector<glm::vec3>& position) {

    vertices = {  
      0.5f,  0.5f, 0.0f,  
      0.5f, -0.5f, 0.0f,  
     -0.5f, -0.5f, 0.0f,  
     -0.5f,  0.5f, 0.0f  
    };

    indexes = {
      0, 1, 3,  
      1, 2, 3 
    };
    
    glGenVertexArrays(1,&VAO_Instanced);
    glGenBuffers(1,&VBO_Instanced);
    glGenBuffers(1,&VBO_Instanced_position);
    glGenBuffers(1,&EBO_Instanced);

    glBindVertexArray(VAO_Instanced);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Instanced);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //instance buffer loading
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glBufferData(GL_ARRAY_BUFFER,position.size() * sizeof(glm::vec3), 
      &position[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);	
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
  }

  void draw() const {  

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void drawInstanced(const int& count) const {

    glBindVertexArray(VAO_Instanced);
    glDrawElementsInstanced(GL_TRIANGLES,6,GL_UNSIGNED_INT,0,count);
    glBindVertexArray(0);
  }
};

struct Circle : public Object {

  Circle() {

    generateVertices();
    generateIndides();

    load();
    loadInstanced();  //this make sure vertex_positions in shader is defaulted to vec3(0,0,0) 
                     //necessary if instancedDraw() is not used
  }

  ~Circle() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);
  }

  void generateVertices(const int& number_vertices = 32) {

    vertices.clear();

    int min = std::max(number_vertices,3);
    float step = (2.0 * std::numbers::pi) / min;

    for (int i = 0; i < min; ++i) {

      vertices.push_back(std::cos(i * step));
      vertices.push_back(std::sin(i * step));
      vertices.push_back(0.0f);
    }
  }

  void generateIndides(const int& number_vertices = 32) {

    indexes.clear();

    int number_indices = std::max(1,number_vertices - 1);
    
    for (int i = 1, j = 2; i < number_indices; ++i, ++j) {

      indexes.push_back(0);
      indexes.push_back(i);
      indexes.push_back(j);
    }
  }

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }

  void loadInstanced() {

    static std::vector<glm::vec3> position = { glm::vec3(0.0,0.0,0.0) };
    loadInstanced(position);
  }

  void loadInstanced(const std::vector<glm::vec3>& position) {

    glGenVertexArrays(1,&VAO_Instanced);
    glGenBuffers(1,&VBO_Instanced);
    glGenBuffers(1,&EBO_Instanced);

    glBindVertexArray(VAO_Instanced);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO_Instanced);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //instance buffer loading
    glGenBuffers(1,&VBO_Instanced_position);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glBufferData(GL_ARRAY_BUFFER,position.size() * sizeof(glm::vec3), 
      &position[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);	
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
  }

  void draw() const {

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void drawInstanced(const int& count) const {

    glBindVertexArray(VAO_Instanced);
    glDrawElementsInstanced(GL_TRIANGLES,indexes.size(),GL_UNSIGNED_INT,0,count);
    glBindVertexArray(0);
  }
};

struct Cube : public Object {

  Cube() {
    load();
  }

  ~Cube() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);
  }

  void load() {

    vertices = {  
      0.5, 0.5, -0.5,
     -0.5, 0.5, -0.5,
     -0.5, 0.5, 0.5,
      0.5, 0.5, 0.5,
      0.5, -0.5, -0.5,
     -0.5, -0.5, -0.5,
     -0.5, -0.5, 0.5,
      0.5, -0.5, 0.5
    };

    indexes = {
      0, 1, 2, 
      0, 2, 3, 
      0, 4, 5, 
      0, 5, 1, 
      1, 5, 6, 
      1, 6, 2, 
      2, 6, 7, 
      2, 7, 3, 
      3, 7, 4, 
      3, 4, 0, 
      4, 7, 6, 
      4, 6, 5 
    };

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }

  void draw() const {

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
};  