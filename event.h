#pragma once

#include <string>
#include <iostream>

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "camera.h"


struct State {

  bool mouse_scroll_up = false;
  bool mouse_scroll_down = false;

} state;

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {

  if (y_offset >= 0) {
    state.mouse_scroll_up = true;
    return;
  }

  else if (y_offset <= 0) {
    state.mouse_scroll_down = true;
    return;
  }
}

struct Event {

  Event() {}

  void poll() const {
		glfwPollEvents();
  }
      
  void processInput(GLFWwindow *window, Camera* camera) const {
    
    //keyboard
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
			glfwSetWindowShouldClose(window,true);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
      camera->ProcessKeyboard(CameraMovement::LEFT);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
      camera->ProcessKeyboard(CameraMovement::RIGHT);
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
      camera->ProcessKeyboard(CameraMovement::UP);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
      camera->ProcessKeyboard(CameraMovement::DOWN);
    
    //mouse scroll
    glfwSetScrollCallback(window,scroll_callback);

    if (state.mouse_scroll_up) {
      camera->ProcessKeyboard(CameraMovement::FORWARD);
      state.mouse_scroll_up = false;
    } 

    else if (state.mouse_scroll_down) {
      camera->ProcessKeyboard(CameraMovement::BACKWARD);
      state.mouse_scroll_down = false;
    }
  }

  template<class Lambda>
  void run(GLFWwindow *window, Camera* camera, const Lambda& event_lambda) const {
    
    event_lambda();
    poll();
		processInput(window,camera);
  }

};