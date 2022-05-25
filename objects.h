#pragma once

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Object {

  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;

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

  const float vertices[9] = {

   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
  }; 

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

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

  const float vertices[12] = {
      0.5f,  0.5f, 0.0f,  
      0.5f, -0.5f, 0.0f,  
      -0.5f, -0.5f, 0.0f,  
      -0.5f,  0.5f, 0.0f  
  };

  const unsigned int indices[6] = {  
      0, 1, 3,  
      1, 2, 3    
  }; 

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

struct Cube : public Object {

  Cube() {
    load();
  }

  ~Cube() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);
  }

  const float vertices[24] = {

    0.5, 0.5, -0.5,
    -0.5, 0.5, -0.5,
    -0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5, -0.5, 0.5,
    0.5, -0.5, 0.5
  };

  const unsigned int indices[36] = {  
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

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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