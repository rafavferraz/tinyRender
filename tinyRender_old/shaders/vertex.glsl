#version 430 core

layout (location=0) in vec3 position;
layout (location=1) in mat4 model_matrix;
layout (location=5) in vec4 color_vec;

out vec4 color;

uniform mat4 projection_matrix;

void main()
{

   gl_Position =  projection_matrix * model_matrix * vec4(position, 1.0);
   color = color_vec;
}
