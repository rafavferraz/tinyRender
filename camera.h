#pragma once

#include <vector>

#include "dependencies/glad/include/glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement { FORWARD, BACKWARD, UP, DOWN, LEFT, RIGHT,
                            PITCH_UP, PITCH_DOWN,
                            YAW_LEFT, YAW_RIGHT
                           };

//default camera values
const float YAW          = -90.0f;
const float YAW_SPEED    = 15.0f;

const float PITCH        =  0.0f;
const float PITCH_SPEED  =  15.0f;

const float SPEED        =  1.5f;
const float SCROLL_SPEED =  15.0f * 1; //5'000

const float SENSITIVITY  =  0.1f;
const float ZOOM         =  45.0f;

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
         scroll_speed(SCROLL_SPEED), 
         mouse_sensitivity(SENSITIVITY), 
         zoom(ZOOM) {

    updateCameraVectors();
  }

  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 world_up;

  //euler angles
  float yaw;
  float pitch;

  //camera options
  float movement_speed;
  float scroll_speed;
  float mouse_sensitivity;
  float zoom;

  void updateCameraVectors() {
    
    //calculate new front vector
    front.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front.y = std::sin(glm::radians(pitch));
    front.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front = glm::normalize(front);

    //re-calculate the right and up vector
    right = glm::normalize(glm::cross(front, world_up));  
    up = glm::normalize(glm::cross(right, front));
  }

  glm::mat4 getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
  }

//name it processInput
  void processKeyboard(CameraMovement direction, double delta_time) {
  
    float velocity = movement_speed * delta_time;
    float scroll_velocity = scroll_speed * delta_time;
    float pitch_velocity = PITCH_SPEED * delta_time;
    float yaw_velocity = YAW_SPEED * delta_time;

    if (direction == CameraMovement::FORWARD)
      position += front * scroll_velocity;
    else if (direction == CameraMovement::BACKWARD)
      position -= front * scroll_velocity;

    if (direction == CameraMovement::LEFT)
      position -= right * velocity;
    else if (direction == CameraMovement::RIGHT)
      position += right * velocity;
    else if (direction == CameraMovement::UP)
      position += up * velocity;
    else if (direction == CameraMovement::DOWN)
      position -= up * velocity;

    if (direction == CameraMovement::PITCH_DOWN) 
      pitch -= pitch_velocity;
    else if (direction == CameraMovement::PITCH_UP) 
      pitch += pitch_velocity;
    
    if (direction == CameraMovement::YAW_LEFT) 
      yaw -= yaw_velocity;
    else if (direction == CameraMovement::YAW_RIGHT) 
      yaw += yaw_velocity;

    updateCameraVectors();
  }

  void setPosition(const glm::vec3& new_position) {

    position = new_position;
    updateCameraVectors();
  }

  // void lookAt() {
  //   //...
  // }

};