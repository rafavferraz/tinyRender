#pragma once

#include <string>
#include <iostream>

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 6

struct Window {

  Window(const std::string& window_name,
         unsigned int screen_width, 
         unsigned int screen_height,
         unsigned int screen_x_position = 0, 
         unsigned int screen_y_position = 0):
         window_name(window_name), screen_width(screen_width), 
         screen_height(screen_height), screen_x_position(screen_x_position),
         screen_y_position(screen_y_position) {

           initialize();
         }

  std::string window_name;
  int screen_width;
  int screen_height;
  int screen_x_position;
  int screen_y_position;

  GLFWwindow* window_ptr;

  void initialize() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ptr = glfwCreateWindow(screen_width,screen_height,window_name.c_str(),NULL,NULL);

    if (window_ptr == NULL) {
      std::cout << "Error @ Window. Failed to create GLFW window." << std::endl;
      glfwTerminate();
    }

    glfwMakeContextCurrent(window_ptr);
    glfwSetFramebufferSizeCallback(window_ptr,framebufferSizeCallback);

    //load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Error @ Window. Failed to initialize GLAD" << std::endl;
    } 
  }

  void terminate() {
    glfwTerminate();
  }

  static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {

    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
  }

};