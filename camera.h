#pragma once

#include <vector>

#include "dependencies/glad/include/glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement { FORWARD, BACKWARD, UP, DOWN, LEFT, RIGHT };

//default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

struct Camera {

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
         float yaw = YAW, 
         float pitch = PITCH): 
         position(position),
         front(glm::vec3(0.0f, 0.0f, -1.0f)), 
         world_up(up),
         yaw(yaw),
         pitch(pitch),
         movement_speed(SPEED), 
         mouse_sensitivity(SENSITIVITY), 
         zoom(ZOOM) {

    updateCameraVectors();
  }

  void updateCameraVectors() {
    
    //calculate new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    //re-calculate the right and up vector
    right = glm::normalize(glm::cross(front, world_up));  
    up = glm::normalize(glm::cross(right, front));
  }

  glm::mat4 GetViewMatrix() {
    return glm::lookAt(position, position + front, up);
  }

  void ProcessKeyboard(CameraMovement direction, float delta_time = 0.05f) {
  
    float velocity = movement_speed * delta_time;

    if (direction == CameraMovement::FORWARD)
      position += front * velocity * 5.0f;
    else if (direction == CameraMovement::BACKWARD)
      position -= front * velocity * 5.0f;
    else if (direction == CameraMovement::LEFT)
      position -= right * velocity;
    else if (direction == CameraMovement::RIGHT)
      position += right * velocity;
    else if (direction == CameraMovement::UP)
      position += up * velocity;
    else if (direction == CameraMovement::DOWN)
      position -= up * velocity;
  }

  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 world_up;

  //euler Angles
  float yaw;
  float pitch;

  //camera options
  float movement_speed;
  float mouse_sensitivity;
  float zoom;

};