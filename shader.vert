#version 460 core

// T * R * S
// V_clip = M_proj * M_view * M_model * V_local

// M_model = transform into world coord
// M_view = camera of OpenGL (camera's point of view)
// M_proj = transforn vertex coord into clip space range(-1000,1000) -> (-1,1)

layout (location = 0) in vec3 vertex_position; //instanced attribute
layout (location = 1) in vec3 model_position;  //object's position of center_of_mass

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
