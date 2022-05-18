#ifndef CAMERA_H
#define CAMERA_H

#include "/code/Math/Containers/vec3.h"
#include "/code/Math/Containers/mat4.h"
#include "/code/Math/LinearAlgebra/linear_algebra.h"

#define CAMERA_ROTATIONAL_SPEED 1.0
#define CAMERA_PANNING_SPEED    0.1
#define CAMERA_MOVEMENT_SPEED   0.001

#define CAMERA_POSITION vec3<float>(0,0,8)
#define CAMERA_TARGET   vec3<float>(0,0,0)
#define CAMERA_UP_AXIS  vec3<float>(0,1,0)

using namespace math::linear_algebra;

//<V> can be just a float..

template<typename V = float>
 struct Camera {

  Camera();
  Camera(const vec3<V> &pos, const vec3<V> &tar, const vec3<V> &up);

  void CalculateR();
  void CalculateDR();
  void CalculateWorldToViewMatrix();
  mat4<V> GetWorldToViewMatrix();

  void MoveUp();
  void MoveDown();
  void MoveForward();
  void MoveBackward();
  void MoveLeft();
  void MoveRight();

  void MoveToOrigin();

  void PannigXClockwise();    //panning around the x-axis counter-clockwise
  void PannigXCounterClockwise();
  void PannigYClockwise();
  void PannigYCounterClockwise();

  void PitchCounterClockwise(); //MAKE!
  void PitchClockwise();
  void YawCounterClockwise();
  void YawClockwise();
  void RollCounterClockwise();
  void RollClockwise();

  void SetPosition(const vec3<V> &pos);
  void SetTarget(const vec3<V> &tar);
  void SetUpAxis(const vec3<V> &up);
  void SetMovementSpeed(const V &mov);
  void SetRotationalSpeed(const V &rot);

  vec3<V> position;
  vec3<V> target;

  vec3<V> up_axis;
  vec3<V> direction;
  vec3<V> right_axis;

  vec3<V> init_position;
  vec3<V> init_target;
  vec3<V> init_up_axis;

  V rotational_speed;
  V panning_speed;
  V movement_speed;

  mat4<V> projection_matrix;
};

template<typename V>
 Camera<V>::Camera(): position(CAMERA_POSITION),
                      target(CAMERA_TARGET),
                      up_axis(CAMERA_UP_AXIS),
                      init_position(CAMERA_POSITION),
                      init_target(CAMERA_TARGET),
                      init_up_axis(CAMERA_UP_AXIS),
                      rotational_speed(CAMERA_ROTATIONAL_SPEED),
                      panning_speed(CAMERA_PANNING_SPEED),
                      movement_speed(CAMERA_MOVEMENT_SPEED) {

    CalculateDR();
    projection_matrix = GetWorldToViewMatrix ();
  }

template<typename V>
 Camera<V>::Camera(const vec3<V> &pos, const vec3<V> &tar, const vec3<V> &up) {

  position = pos;
  target = tar;
  up_axis = up;

  init_position = pos;
  init_target = tar;
  init_up_axis = up;

  rotational_speed = V(CAMERA_ROTATIONAL_SPEED);
  panning_speed = V(CAMERA_PANNING_SPEED);
  movement_speed = V(CAMERA_MOVEMENT_SPEED);

  CalculateDR();
  projection_matrix = GetWorldToViewMatrix ();
}

template<typename V>
 void Camera<V>::MoveUp() {
  position += up_axis*movement_speed;
}

template<typename V>
 void Camera<V>::MoveDown() {
  position -= up_axis*movement_speed;
}

template<typename V>
 void Camera<V>::MoveForward() {
  position -= direction*movement_speed;
}

template<typename V>
 void Camera<V>::MoveBackward() {
  position += direction*movement_speed;
}

template<typename V>
void Camera<V>::MoveLeft() {
 position -= right_axis*movement_speed;
}

template<typename V>
 void Camera<V>::MoveRight() {
 position += right_axis*movement_speed;
}

template<typename V>
 void Camera<V>::MoveToOrigin () {

  position = init_position;
  target = init_target;
  up_axis = init_up_axis;

  CalculateDR();
}

template<typename V>
 void Camera<V>::PannigXClockwise () {

  position = RotationX (rotational_speed) * position;
  direction = Normalize(position - target);
  up_axis = Normalize(CrossProduct(direction,right_axis));
}

template<typename V>
 void Camera<V>::PannigXCounterClockwise () {

  position = RotationX (-rotational_speed) * position;
  direction = Normalize(position - target);
  up_axis = Normalize(CrossProduct(direction,right_axis));
}

template<typename V>
 void Camera<V>::PannigYClockwise () {

  position = RotationY (-panning_speed) * position;
  CalculateDR ();
}

//KP_6
template<typename V>
 void Camera<V>::PannigYCounterClockwise () {

  position = RotationY (panning_speed) * position;
  CalculateDR ();
}

template<typename V>
 void Camera<V>::PitchClockwise () {

  direction = Normalize (RotationX (rotational_speed) * direction);
  up_axis = Normalize (CrossProduct (direction,right_axis));
}

template<typename V>
 void Camera<V>::PitchCounterClockwise () {

  direction = Normalize (RotationX (-rotational_speed) * direction);
  up_axis = Normalize (CrossProduct (direction,right_axis));
}

template<typename V>
 void Camera<V>::YawClockwise () {

  direction =  Normalize (RotationY (-rotational_speed) * direction);
  right_axis = Normalize (CrossProduct (up_axis,direction));
}

template<typename V>
 void Camera<V>::YawCounterClockwise () {

  direction =  Normalize (RotationY (rotational_speed) * direction);
  right_axis = Normalize (CrossProduct (up_axis,direction));
}

template<typename V>
 void Camera<V>::CalculateR() {
  right_axis = Normalize(CrossProduct(up_axis,direction));
}

template<typename V>
 void Camera<V>::CalculateDR() {

  direction = Normalize(position - target);
  right_axis = Normalize(CrossProduct(up_axis,direction));
}

//main function
template<typename V>
 void Camera<V>::CalculateWorldToViewMatrix() {

  //CalculateDR();     <-MAYBE IS NECESSARY!!!!
  projection_matrix = LookAt(right_axis,up_axis,direction,position);
}

//main function
template<typename V>
 mat4<V> Camera<V>::GetWorldToViewMatrix() {

  //CalculateDR();     //<-MAYBE IS NECESSARY!!!!
  return math::linear_algebra::LookAt(right_axis,up_axis,direction,position);
}

template<typename V>
 void Camera<V>::SetPosition(const vec3<V> &pos) {
  position = pos;
 }

template<typename V>
void Camera<V>::SetTarget(const vec3<V> &tar) {
 target = tar;
}

template<typename V>
 void Camera<V>::SetUpAxis(const vec3<V> &up) {
  up_axis = up;
 }

template<typename V>
 void Camera<V>::SetMovementSpeed(const V &mov) {
  movement_speed = mov;
}

template<typename V>
 void Camera<V>::SetRotationalSpeed(const V &rot) {
  rotational_speed = rot;
}



#endif // CAMERA_H
