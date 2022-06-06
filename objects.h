#pragma once

#include <numbers>

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Object {

  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;

  std::vector<float> vertices;
  std::vector<unsigned int> indexes;

  void load();
  void draw() const ;
};

struct Triangle : public Object {

  Triangle() {
    load();
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

  void draw() const {

    glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
  }
};

struct Square : public Object {

  Square() {
    load();
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

  void draw() const {

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
};

struct Circle : public Object {

  Circle() {
    load();
  }

  ~Circle() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);
  }

  void generateVertices(const int& number_vertices) {

    int min = std::max(number_vertices,3);
    float step = (2.0 * std::numbers::pi) / min;

    for (int i = 0; i < min; ++i) {

      vertices.push_back(std::cos(i * step));
      vertices.push_back(std::sin(i * step));
      vertices.push_back(0.0f);
    }
  }

  void generateIndides(const int& number_vertices) {

    int number_indices = std::max(1,number_vertices - 1);
    
    for (int i = 1, j = 2; i < number_indices; ++i, ++j) {

      indexes.push_back(0);
      indexes.push_back(i);
      indexes.push_back(j);
    }
  }

  void load(const int& number_vertices = 32) {

    generateVertices(number_vertices);
    generateIndides(number_vertices);

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
    glDrawElements(GL_TRIANGLES, indexes.size() * 3, GL_UNSIGNED_INT, 0);
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