#pragma once

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "shader.h"
#include "objects.h"


struct Render {

  Render() {

    glEnable(GL_DEPTH_TEST);

    //load default shader
    shader = Shader("./shader.vert","./shader.frag");
    shader.use();  

    camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f));
  }

  ~Render() {
    shader.deleteShader();
  }

  Triangle triangle;
  Square square;

  glm::mat4 transform = glm::mat4(1.0f);

  Shader shader;
  Camera camera;

  void clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }


  void drawTriangle() {
    triangle.draw();
  }

  void drawSquare() {
    square.draw();
  }


  void pushMatrix() {

		transform = glm::mat4(1.0f);
		shader.setUniformMat4("transform",transform);
  }

  void translate(const glm::vec3& value) {

    transform = glm::translate(transform,value);
		shader.setUniformMat4("transform",transform);
  }

  void popMatrix() {

		transform = glm::mat4(1.0f);
		shader.setUniformMat4("transform",transform);
  }


  void cameraBegin() {

		glm::mat4 view_matrix = camera.GetViewMatrix();
		glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 100.0f);
		
		shader.setUniformMat4("view",view_matrix);
		shader.setUniformMat4("projection",projection_matrix);
  }

  void cameraEnd() {

		glm::mat4 view_matrix = glm::mat4(1.0f);
		glm::mat4 projection_matrix = glm::mat4(1.0f);
		
		shader.setUniformMat4("view",view_matrix);
		shader.setUniformMat4("projection",projection_matrix);
  }

  void background(const glm::vec4& color) {
		glClearColor(color.x,color.y,color.z,color.w);
  }



};