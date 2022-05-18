#ifndef TINYRENDER_H
#define TINYRENDER_H

#include "input.h"
#include "camera.h"
#include "render.h"
#include "window.h"


struct TinyRender {

  TinyRender(): run_flag(true) {

    perspective_matrix = render.getPerspectiveMatrix();
    projection_matrix = getProjectionMatrix ();

  	window.Init();
  	render.Init();
  }


//maybe just use one buffer for all? what are the adv of multiple buffers?
  template<typename T>
   void InitBuffer(const std::vector<T>& objects, 
   	               const std::vector<mat4<float>>& model_matrices) {

    render.buffer_prim_.GenerateBuffers ();
    render.buffer_prim_.InitAllBuffers (objects.begin (),
                                        objects.end(),
                                        render.prim_shader_data.begin (),
                                        render.prim_shader_data.end (),
                                        model_matrices.begin (),
                                        model_matrices.end ());
  }

  template<typename T>
   void Draw(const std::vector<T>& objects, 
   	         const std::vector<mat4<float>>& transforms) {

    //input
    input.ReadInput();
    run_flag = input.ProcessInput (&camera);


    //update buffers
    render.buffer_prim_.UpdateModelMatrixBuffer(transforms.begin (),
                                                transforms.end ());
    //draw
    render.Clear();
    projection_matrix = getProjectionMatrix();
    render.buffer_prim_.Draw(projection_matrix,objects.begin (),objects.end ());
   

    //swap buffers
    SDL_GL_SwapWindow(window.getWindow());
  }	

  template<typename T>
   void AddColor(const int& obj_position, const T& object, 
   	             const vec4<float>& color) {

    ObjectShaderData shader_data;
    shader_data.color.insert (shader_data.color.end (), 
    	                      object.vertices.size (),
                              color);

    render.prim_shader_data.push_back(shader_data);
  }

  void ChangeCameraPositionWrapper() { //change initialization(step = 0) camera pos

  }

  mat4<float> getProjectionMatrix() {
    return perspective_matrix * camera.GetWorldToViewMatrix ();
  }


  Input  input;
  Window window;
  Camera<float> camera;
  Render<vec3<float>> render;  //change //can have multiple renders, or views

  std::vector<mat4<float>> model_matrices;

  mat4<float> perspective_matrix;
  mat4<float> projection_matrix;  //perspective_m * camera->GetWorldToViewMatrix ()

  bool run_flag;

};




#endif  //TINYRENDER_H