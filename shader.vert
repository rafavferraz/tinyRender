#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 transform;   //object's own transform

uniform mat4 model;       //render.pushMatrix()
uniform mat4 view;        //render.cameraBegin()
uniform mat4 projection;  //render.cameraBegin()

uniform vec4 color;       //render.setColor();

out vec4 fragment_color;

void main() {

  gl_Position = projection * view * model * (transform * vec4(position, 1.0f));
  fragment_color = color;
}