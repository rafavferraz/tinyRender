#version 460 core

layout (location = 0) in vec3 position;

uniform mat4 transform;   //render.pushMatrix()
uniform mat4 view;        //render.cameraBegin()
uniform mat4 projection;  //render.cameraBegin()

uniform vec4 color;       //render.setColor();

out vec4 fragment_color;

void main() {

  gl_Position = projection * view * transform * vec4(position, 1.0f);
  fragment_color = color;
}