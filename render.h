#pragma once

#include "../../utility/clock.h"

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "shader.h"
#include "objects.h"
#include "window.h"


template<class WindowType>
struct Render {

  Render(const std::string& window_name,
         unsigned int screen_width, 
         unsigned int screen_height,
         unsigned int screen_x_position = 0, 
         unsigned int screen_y_position = 0): 
         window(window_name,screen_width,screen_height,screen_x_position,screen_y_position),
         shader("./shader.vert","./shader.frag") {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_DEPTH_TEST);

		glm::mat4 transform_matrix = glm::mat4(1.0f);
    glm::mat4 view_matrix = glm::mat4(1.0f);
		glm::mat4 projection_matrix = glm::mat4(1.0f);
		
		shader.setUniformMat4("transform",transform_matrix);
		shader.setUniformMat4("view",view_matrix);
		shader.setUniformMat4("projection",projection_matrix);

    camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f));
  }

  ~Render() {
  }

  Window<WindowType> window;
  Shader shader;
  Camera camera;

  Triangle triangle;
  Square square;
  Cube cube;

  glm::mat4 transform = glm::mat4(1.0f);

  void drawTriangle() const {
    triangle.draw();
  }

  void drawSquare() const {
    square.draw();
  }

  void drawCube() const {
    cube.draw();
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

  void cameraBegin() const {

		glm::mat4 view_matrix = camera.getViewMatrix();
		glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.1f, 1000.0f);
		
		shader.setUniformMat4("view",view_matrix);
		shader.setUniformMat4("projection",projection_matrix);
  }

  void cameraEnd() const {

		glm::mat4 view_matrix = glm::mat4(1.0f);
		glm::mat4 projection_matrix = glm::mat4(1.0f);
		
		shader.setUniformMat4("view",view_matrix);
		shader.setUniformMat4("projection",projection_matrix);
  }

  void clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void background(const glm::vec4& color) const {
		glClearColor(color.x,color.y,color.z,color.w);
  }

  void setColor(const glm::vec4& color) const{
		shader.setUniformVec4("color",color);		
  }

  template<class SetupFunction, class UpdateFunction, class DrawFunction, class EventFunction>
  void loop(const SetupFunction& setupFunction, const UpdateFunction& updateFunction, 
            const DrawFunction& drawFunction, const EventFunction& eventFunction,
            const bool& print_clock = false) {
    
    setupFunction();
    window.loop(&camera,updateFunction,drawFunction,eventFunction,[&](){clear();},print_clock);
  }
};