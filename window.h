#pragma once

#include <string>
#include <iostream>

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "camera.h"

#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 6


// namespace tinyrender {


namespace window {

  struct GLFW {};

}

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double x_offset, double y_offset);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

template<typename WindowType> struct Window;

template<>
struct Window<window::GLFW> {

  Window(const std::string& window_name,
         unsigned int screen_width, 
         unsigned int screen_height,
         unsigned int screen_x_position, 
         unsigned int screen_y_position):
         window_name(window_name), screen_width(screen_width), 
         screen_height(screen_height), screen_x_position(screen_x_position),
         screen_y_position(screen_y_position) {
         
           glfwInit();
           glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
           glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
           glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
           glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
           glfwWindowHint(GLFW_SAMPLES, 4);

           #ifdef __APPLE__
             glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
           #endif

           window_ptr = glfwCreateWindow(screen_width,screen_height,window_name.c_str(),NULL,NULL);

           if (window_ptr == NULL) {
            std::cout << "Error @ Window. Failed to create GLFW window." << std::endl;
            glfwTerminate();
           }

           glfwMakeContextCurrent(window_ptr);

           glfwSetWindowPos(window_ptr,screen_x_position,screen_y_position);

           //1 v-syncs to 60 hz, 0 goes as fast as it can...
           glfwSwapInterval(0);
          //  glfwSwapInterval(1);

           //load all OpenGL function pointers
           if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Error @ Window. Failed to initialize GLAD" << std::endl;
           } 

           //setting callbacks
           glfwSetFramebufferSizeCallback(window_ptr,framebufferSizeCallback);
           glfwSetMouseButtonCallback(window_ptr,mouseButtonCallback);
           glfwSetScrollCallback(window_ptr,scrollCallback);  
           glfwSetCursorPosCallback(window_ptr,cursorPositionCallback);

           //default init maouse position
           glfwGetCursorPos(window_ptr,&state.cursor_x_position,&state.cursor_y_position);
         }

  ~Window() {
    glfwTerminate();
  }

  std::string window_name;
  int screen_width;
  int screen_height;
  int screen_x_position;
  int screen_y_position;

  GLFWwindow* window_ptr;

  void processInput(Camera* camera, double delta_time) const {
    
    //keyboard
    if (glfwGetKey(window_ptr,GLFW_KEY_A) == GLFW_PRESS) 
      camera->processKeyboard(CameraMovement::LEFT,delta_time,state);
    else if (glfwGetKey(window_ptr,GLFW_KEY_D) == GLFW_PRESS) 
      camera->processKeyboard(CameraMovement::RIGHT,delta_time,state);
    else if (glfwGetKey(window_ptr,GLFW_KEY_W) == GLFW_PRESS) 
      camera->processKeyboard(CameraMovement::UP,delta_time,state);
    else if (glfwGetKey(window_ptr,GLFW_KEY_S) == GLFW_PRESS) 
      camera->processKeyboard(CameraMovement::DOWN,delta_time,state);
    else if(glfwGetKey(window_ptr,GLFW_KEY_ESCAPE) == GLFW_PRESS) 
			glfwSetWindowShouldClose(window_ptr,true);

    //mouse buttons
    if(state.mouse_button_left_press) {
			// OUTPUT("button L pressed")
    }

    else if(state.mouse_button_middle_press) {
			// OUTPUT("button M pressed")
    }

    //left button hold condition
    if(!state.mouse_button_left_release) {

      if (state.cursor_y_offset > 0.0) {
        camera->processKeyboard(CameraMovement::PITCH_UP,delta_time,state);
      }

      else if (state.cursor_y_offset < 0.0) {
        camera->processKeyboard(CameraMovement::PITCH_DOWN,delta_time,state);
      }

      if (state.cursor_x_offset > 0.0) {
        camera->processKeyboard(CameraMovement::YAW_LEFT,delta_time,state);
      }

      else if (state.cursor_x_offset < 0.0) {
        camera->processKeyboard(CameraMovement::YAW_RIGHT,delta_time,state);
      }
    }

    //middle button hold condition
    if(!state.mouse_button_middle_release) {
    
      //checking mouse movement
      if (state.cursor_y_offset > 0.0) {
        camera->processKeyboard(CameraMovement::DOWN,delta_time,state);
      }

      else if (state.cursor_y_offset < 0.0) {
        camera->processKeyboard(CameraMovement::UP,delta_time,state);
      }

      if (state.cursor_x_offset > 0.0) {
        camera->processKeyboard(CameraMovement::RIGHT,delta_time,state);
      }

      else if (state.cursor_x_offset < 0.0) {
        camera->processKeyboard(CameraMovement::LEFT,delta_time,state);
      }
    }

    //mouse scroll
    if (state.mouse_scroll_up) {
      camera->processKeyboard(CameraMovement::FORWARD,delta_time,state);  
    } 

    else if (state.mouse_scroll_down) {
      camera->processKeyboard(CameraMovement::BACKWARD,delta_time,state);  
    }

    state.clear();
  }

  template<class UpdateFunction, class DrawFunction, class EventFunction, class ClearFunction>
  void loop(Camera* camera, 
            const UpdateFunction& updateFunction, 
            const DrawFunction& drawFunction, 
            const EventFunction& eventFunction,
            const ClearFunction& clearFunction,
            const bool& print_clock) {
    
    double current_time = 0.0;
    ClockAveraged<clock_precision::seconds> clock_loop;

    while (!glfwWindowShouldClose(window_ptr)) {

      clearFunction();

      clock_loop.tic();

        updateFunction();
        clearFunction();
        drawFunction();

        glfwSwapBuffers(window_ptr);

        glfwPollEvents();
        processInput(camera,current_time);
        eventFunction();

        glfwGetWindowSize(window_ptr,&screen_width,&screen_height);

      clock_loop.toc();

      if (clock_loop.hasElapsed(milliseconds(500))) {

        current_time = clock_loop.get();
        double fps = 1.0d / current_time;

        if (print_clock)
          OUTPUT(clock_loop,fps)
      }
    }
  }
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0,0,width,height);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

  //left button
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    state.mouse_button_left_press = true;
    state.mouse_button_left_release = false;
  }

  else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    state.mouse_button_left_press = false;
    state.mouse_button_left_release = true;
  }

  //middle button
  if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
    state.mouse_button_middle_press = true;
    state.mouse_button_middle_release = false;
  }

  else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) {
    state.mouse_button_middle_press = false;
    state.mouse_button_middle_release = true;
  }
}

void scrollCallback(GLFWwindow* window, double x_offset, double y_offset) {

  if (y_offset >= 0) {
    state.mouse_scroll_up = true;
    state.mouse_scroll_up_offset = y_offset;
  }

  else if (y_offset <= 0) {
    state.mouse_scroll_down = true;
    state.mouse_scroll_down_offset = y_offset;
  }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {

  state.cursor_x_offset = state.cursor_x_position - xpos;
  state.cursor_y_offset = state.cursor_y_position - ypos;

  state.cursor_x_position = xpos;
  state.cursor_y_position = ypos;
}


// namespace tinyrender 