#pragma once

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Object {

  unsigned int VAO;
  unsigned int VBO;

  void load();
  void draw();
};

struct Triangle : public Object {

  Triangle() {
    load();
  }

  ~Triangle() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  // glDeleteBuffers(1, &EBO);
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

  void draw() {

    glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

struct Square : public Object {

  Square() {
    load();
  }

  ~Square() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  // glDeleteBuffers(1, &EBO);
  }

  const float vertices[18] = {
    // first triangle
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f,  0.5f, 0.0f,  // top left 

    // second triangle
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
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

  void draw() {

    glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
  }
};