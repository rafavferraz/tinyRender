#include <iostream>
#include <vector>

#include "tinyrender.h"

#include "/code/LagrangePhysics_Alpha /Geometry/polygon_generator.h"
#include "/code/LagrangePhysics_Alpha /Geometry/polyhedron_generator.h"
#include "/code/LagrangePhysics_Alpha /Geometry/polygon.h"
#include "/code/Utility/print.h"
#include "/code/Utility/clock.h"
#include "/code/Math/Containers/vec4.h"

struct Object {

  std::vector<vec3<double>> vertices;
  std::vector<int> indices;
};

int main(int argc, char *argv[]) {


  TinyRender render;

  Clock<precision::microseconds> clock;
  std::vector<Object> objects;
  std::vector<mat4<float>> model_matrices;


  //render.AddSquare(0.5);  //no objects necessary, no model matrices

  //create objects
  Object box;
  geometry::generator::Box(vec3<double>(0.5),&box.vertices,&box.indices);
  objects.push_back(box);


  //create model matrix
  model_matrices.push_back(mat4<float>());
  
  //add color, create a default color, fix seg fault when color is not init
  render.AddColor(0,box,vec4<float>(0.4,0.4,0.7,1.0)); 

  //init buffers
  render.InitBuffer(objects,model_matrices);


  while (render.run_flag) {

   
    clock.tic();
    render.Draw(objects,model_matrices); 
    clock.toc_avg();


  }

  OUTPUT(clock)



  return 0;
}