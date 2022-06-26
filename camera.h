#pragma once

#include <vector>
#include <algorithm>

#include "dependencies/glad/include/glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "state.h"


namespace tinyrender {


enum class CameraMovement { FORWARD, BACKWARD, UP, DOWN, LEFT, RIGHT,
                            PITCH_UP, PITCH_DOWN,
                            YAW_LEFT, YAW_RIGHT
                           };

//default camera values
const float YAW          = -90.0f;
const float YAW_SPEED    = 4.0f;

const float PITCH        =  0.0f;
const float PITCH_SPEED  =  4.0f;

const float SPEED        =  1.5f;
const float SCROLL_SPEED =  15.0f;

const float SENSITIVITY  =  0.1f;
const float ZOOM         =  45.0f;

struct Camera {

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), //the formula on line 77-79 is only valid for this up configuration
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

//yaw/pitch are global reference!!
  //euler angles
  float yaw;
  float pitch;

  //camera options
  float movement_speed;
  float scroll_speed;
  float mouse_sensitivity;
  float zoom;

//make it read from here!!
  glm::mat4 view_matrix = glm::mat4(1.0f);

// https://gamedev.stackexchange.com/questions/168542/camera-view-matrix-from-position-yaw-pitch-worldup
// http://web.cs.wpi.edu/~emmanuel/courses/cs543/slides/lecture6a.pdf
// https://www.cs.utexas.edu/~theshark/courses/cs354/lectures/cs354-10.pdf
// https://github.com/cgibson/OpenGL-Examples/blob/master/test/camera.cpp
  void updateCameraVectors() {
    
//yaw/pitch are global reference!!
    //calculate new front vector
    glm::vec3 front_temp;
    front_temp.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front_temp.y = std::sin(glm::radians(pitch));
    front_temp.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    front = glm::normalize(front_temp);

    //re-calculate the right and up vector
    right = glm::normalize(glm::cross(front,world_up));  
    up = glm::normalize(glm::cross(right,front));
  }

  void setPosition(const glm::vec3& new_position) {

    position = new_position;
    updateCameraVectors();
  }

  void setTarget(const glm::vec3& target) {

    front = glm::normalize(target - position);
    right = glm::normalize(glm::cross(front,world_up));  
    up = glm::normalize(glm::cross(right,front));

    view_matrix = glm::lookAt(position,target,up);

//yaw/pitch are global reference!!
    yaw = -90.0f;
    pitch = 0.0f;
  }

  glm::mat4 getViewMatrix() {

    view_matrix = glm::lookAt(position, position + front, up);
    return view_matrix;
  }
  
//name it processInput
  void processKeyboard(CameraMovement direction, double delta_time, const State& state) {
  
    float velocity = movement_speed * delta_time;
    float scroll_velocity = scroll_speed * delta_time;
    float pitch_velocity = PITCH_SPEED * delta_time;
    float yaw_velocity = YAW_SPEED * delta_time;

    if (direction == CameraMovement::FORWARD) 
      position += front * scroll_velocity * (float)state.mouse_scroll_up_offset;
    else if (direction == CameraMovement::BACKWARD)
      position += front * scroll_velocity  * (float)state.mouse_scroll_down_offset;

    if (direction == CameraMovement::LEFT)
      position -= right * velocity;
    else if (direction == CameraMovement::RIGHT)
      position += right * velocity;
    else if (direction == CameraMovement::UP)
      position += up * velocity;
    else if (direction == CameraMovement::DOWN)
      position -= up * velocity;

    if (direction == CameraMovement::PITCH_DOWN) {

      pitch -= pitch_velocity * state.cursor_y_offset;
      pitch = std::clamp(pitch,-89.0f,89.0f);
    }
    else if (direction == CameraMovement::PITCH_UP) {

      pitch -= pitch_velocity * state.cursor_y_offset;
      pitch = std::clamp(pitch,-89.0f,89.0f);
    }

    if (direction == CameraMovement::YAW_LEFT) {

      yaw -= yaw_velocity * state.cursor_x_offset;
      yaw = std::clamp(yaw,-180.0f,89.0f);
    }
    else if (direction == CameraMovement::YAW_RIGHT) {

      yaw -= yaw_velocity * state.cursor_x_offset;
      yaw = std::clamp(yaw,-180.0f,89.0f);
    }

    updateCameraVectors();
  }
};


}  // namespace tinyrender