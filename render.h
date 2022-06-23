#pragma once

#include "../../utility/clock.h"

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "window.h"
#include "camera.h"
#include "shader.h"
#include "objects.h"


template<class WindowType>
struct Render {

  Render(const std::string& window_name,
         unsigned int screen_width, 
         unsigned int screen_height,
         unsigned int screen_x_position = 0, 
         unsigned int screen_y_position = 0): 
         window(window_name,screen_width,screen_height,screen_x_position,screen_y_position),
         shader("./shader.vert","./shader.frag"),
         camera(glm::vec3(0.0f,0.0f,10.0f)) {

    initialize();

		glm::mat4 model_matrix = glm::mat4(1.0f);
    glm::mat4 view_matrix = glm::mat4(1.0f);
		glm::mat4 projection_matrix = glm::mat4(1.0f);
		
		shader.setUniformMat4("model",model_matrix);
		shader.setUniformMat4("view",view_matrix);
		shader.setUniformMat4("projection",projection_matrix);

		glm::vec4 color = glm::vec4(1.0f,0.5f,0.2f,1.0f);
		shader.setUniformVec4("color",color);
  }

  Window<WindowType> window;
  Shader shader;
  Camera camera;

  Triangle triangle;
  Square square;
  Circle circle;
  Cube cube;
  Sphere sphere;
  Cone cone;
  Cylinder cylinder;

  glm::mat4 model_matrix = glm::mat4(1.0f);

  void initialize() const {

    glEnable(GL_MULTISAMPLE); 

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glEnable(GL_DEPTH_TEST);

    // glDepthMask(GL_FALSE);
    // glDepthMask(GL_TRUE); 

    // glDepthFunc(GL_ALWAYS); 
    // glDepthFunc(GL_LESS); 
  }

  void clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void fill(const bool& fill_shape) {

    if (fill_shape)
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    else
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  }

  void drawTriangle(const glm::vec3& center, const bool& fill_shape = true) {
    
    pushMatrix();

      fill(fill_shape);
			translate(center);
      triangle.draw();

    popMatrix();
  }

  void drawTriangle(const glm::vec3& center, const float& width, const float& height, const bool& fill_shape = true) {
    
    pushMatrix();

      fill(fill_shape);
			translate(center);
      scale(glm::vec3(width,height,0.0));
      triangle.draw();

    popMatrix();
  }

  void loadTriangleInstanced(const std::vector<glm::vec3>& position) {
    triangle.loadInstanced(position);
  }

  void drawTriangleInstanced(const int& count, const float& width, const float& height, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      scale(glm::vec3(width,height,0.0));
      triangle.drawInstanced(count);

    popMatrix();
  }

  void drawRectangle(const glm::vec3& center, const float& width, 
                  const float& height, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      translate(center);
      scale(glm::vec3(width,height,0.0));
      square.draw();

    popMatrix();
  }

  void drawRectangle(const glm::vec3& center, const float& angle_z_radians, 
                     const float& width, const float& height, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      translate(center);
      rotate(angle_z_radians,glm::vec3(0.0,0.0,1.0));
      scale(glm::vec3(width,height,0.0));
      square.draw();

    popMatrix();
  }

//width and height? why not scale inside transform?
  void drawRectangle(const glm::mat4& transform, const float& width, 
                     const float& height, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);

      // scale(glm::vec3(width,height,0.0));

// new way
      model_matrix = transform * model_matrix;
      shader.setUniformMat4("model",model_matrix);
      square.draw();

// //old way, only works for 2D
//       float translation_x = transform[3][0];
//       float translation_y = transform[3][1];
//       // OUTPUT(translation_x,translation_y)

//       translate(glm::vec3(translation_x,translation_y,0.0));

//       float rotation_xy = transform[0][1];
//       float rotation_yy = transform[1][1];
//       // OUTPUT(rotation_xx,rotation_xy)

//       double angle_z = -std::atan2(rotation_xy,rotation_yy);
//       rotate(angle_z,glm::vec3(0.0,0.0,1.0));

//       square.draw();

    popMatrix();
  }

  void loadRectangleInstanced(const std::vector<glm::vec3>& position) {
    square.loadInstanced(position);
  }

  void drawRectangleInstanced(const int& count, const float& width, 
                              const float& height, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      scale(glm::vec3(width,height,0.0));
      square.drawInstanced(count);

    popMatrix();
  }

  void drawCircle(const glm::vec3& center, const float& radius, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      translate(center);
      scale(glm::vec3(radius,radius,0.0));
      circle.draw();

    popMatrix();
  }

  void loadCircleInstanced(const std::vector<glm::vec3>& position) {
    circle.loadInstanced(position);
  }

  void drawCircleInstanced(const int& count, const float& radius, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      scale(glm::vec3(radius,radius,0.0));
      circle.drawInstanced(count);

    popMatrix();
  }

  void drawCube(const glm::vec3& center, const float& width, const float& height,
                const float& depth, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      translate(center);
      scale(glm::vec3(width,height,depth));
      cube.draw();

    popMatrix();
  }

  void loadCubeInstanced(const std::vector<glm::vec3>& position) {
    cube.loadInstanced(position);
  }

  void drawCubeInstanced(const int& count, const float& width, const float& height,
                         const float& depth, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      scale(glm::vec3(width,height,depth));
      cube.drawInstanced(count);

    popMatrix();
  }

  void drawSphere(const glm::vec3& center, const float& radius, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      translate(center);
      scale(glm::vec3(radius,radius,radius));
      sphere.draw();

    popMatrix();
  }

  void loadSphereInstanced(const std::vector<glm::vec3>& position) {
    sphere.loadInstanced(position);
  }

  void drawSphereInstanced(const int& count, const float& radius, const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      scale(glm::vec3(radius,radius,radius));
      sphere.drawInstanced(count);

    popMatrix();
  }

  void drawCone(const glm::vec3& center, const float& radius, const float& height,
                const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      translate(center);
      scale(glm::vec3(radius,radius,height));
      cone.draw();

    popMatrix();
  }

//is this a easier call??
  void drawCone(const glm::vec3& center, glm::mat4& rotation,
                const float& radius, const float& height,
                const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      translate(center);
      rotate(rotation);
      scale(glm::vec3(radius,radius,height));
      cone.draw();

    popMatrix();
  }

  void loadConeInstanced(const std::vector<glm::vec3>& position) {
    cone.loadInstanced(position);
  }

  void drawConeInstanced(const int& count, const float& radius, const float& height, 
                         const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      scale(glm::vec3(radius,radius,height));
      cone.drawInstanced(count);

    popMatrix();
  }

  void drawCylinder(const glm::vec3& center, const float& radius, const float& height,
                    const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      translate(center);
      scale(glm::vec3(radius,radius,height));
      cylinder.draw();

    popMatrix();
  }

  void drawCylinder(const glm::vec3& center, glm::mat4& rotation,
                    const float& radius, const float& height,
                    const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      translate(center);
      rotate(rotation);
      scale(glm::vec3(radius,radius,height));
      cylinder.draw();

    popMatrix();
  }

  void loadCylinderInstanced(const std::vector<glm::vec3>& position) {
    cylinder.loadInstanced(position);
  }

  void drawCylinderInstanced(const int& count, const float& radius, const float& height, 
                             const bool& fill_shape = true) {

    pushMatrix();

      fill(fill_shape);
      scale(glm::vec3(radius,radius,height));
      cylinder.drawInstanced(count);

    popMatrix();
  }

  void drawAxis() {

    pushMatrix();

      //x-axis, red
      setColor(glm::vec4(1.0f,0.0f,0.0f,1.0f));
      glm::mat4 rotation = glm::rotate(glm::radians(90.0f),glm::vec3(0.0,1.0,0.0));
      drawCylinder(glm::vec3(0.0,0.0,0.0),rotation,0.025,1.0);
      drawCone(glm::vec3(1.0,0.0,0.0),rotation,0.05,0.1);

      //y-axis, green
      setColor(glm::vec4(0.0f,1.0f,0.0f,1.0f));
      rotation = glm::rotate(glm::radians(-90.0f),glm::vec3(1.0,0.0,0.0));
      drawCylinder(glm::vec3(0.0,0.0,0.0),rotation,0.025,1.0);
      drawCone(glm::vec3(0.0,1.0,0.0),rotation,0.05,0.1);

      //z-axis, blue
      setColor(glm::vec4(0.0f,0.0f,1.0f,1.0f));
      drawCylinder(glm::vec3(0.0,0.0,0.0),0.025,1.0);
      drawCone(glm::vec3(0.0,0.0,1.0),0.05,0.1);

      //sphere at center
      setColor(glm::vec4(0.0f,0.0f,0.0f,1.0f));
      scale(glm::vec3(0.075,0.075,0.075));
      sphere.draw();

    popMatrix();
  }

  void scale(const glm::vec3& value) {

    model_matrix = glm::scale(model_matrix,value);
    shader.setUniformMat4("model",model_matrix);
  }

  void translate(const glm::vec3& value) {

    model_matrix = glm::translate(model_matrix,value);
		shader.setUniformMat4("model",model_matrix);
  }

  void rotate(const float& value_radians, const glm::vec3& axis) {

    model_matrix = glm::rotate(model_matrix,value_radians,axis);
		shader.setUniformMat4("model",model_matrix);
  }

  void rotate(const glm::mat4& rotation) {

    model_matrix *= rotation;
		shader.setUniformMat4("model",model_matrix);
  }

  void pushMatrix() {

		model_matrix = glm::mat4(1.0f);
		shader.setUniformMat4("model",model_matrix);
  }

  void popMatrix() {

		model_matrix = glm::mat4(1.0f);
		shader.setUniformMat4("model",model_matrix);
  }

  void cameraBegin() {

    auto screen_width = window.screen_width;
    auto screen_height = window.screen_height;
    auto aspect_ratio = (float)screen_width / screen_height;
    // OUTPUT(screen_width,screen_height)

    float near_clip = 0.01f;
    float far_clip = 1000.0f;
    float fov = glm::radians(45.0f);

		glm::mat4 view_matrix = camera.getViewMatrix();
		glm::mat4 projection_matrix = glm::perspective(fov,aspect_ratio,near_clip,far_clip);
		
		shader.setUniformMat4("view",view_matrix);
		shader.setUniformMat4("projection",projection_matrix);
  }

  void cameraEnd() const {

		glm::mat4 view_matrix = glm::mat4(1.0f);
		glm::mat4 projection_matrix = glm::mat4(1.0f);
		
		shader.setUniformMat4("view",view_matrix);
		shader.setUniformMat4("projection",projection_matrix);
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