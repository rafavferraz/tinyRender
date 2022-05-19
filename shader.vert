#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 transform;   //render.pushMatrix()
uniform mat4 model;
uniform mat4 view;        //render.cameraBegin()
uniform mat4 projection;  //render.cameraBegin()

void main() {

  gl_Position = projection * view * model * transform * vec4(position, 1.0);
}