#version 460 core

layout (location = 0) in vec3 vertex_position; //instanced attribute
layout (location = 1) in vec3 model_position;  //regular center_of_mass

uniform mat4 model;       //render.pushMatrix()
uniform mat4 view;        //render.cameraBegin()
uniform mat4 projection;  //render.cameraBegin()

uniform vec4 color;       //render.setColor();

out vec4 fragment_color;

void main() {

  gl_Position = projection * view  * ((vec4(model_position,1.0f) + 
     model * vec4(vertex_position, 1.0f)));

  fragment_color = color;
}
