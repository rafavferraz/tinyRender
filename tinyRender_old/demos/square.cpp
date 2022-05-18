#include <iostream>
#include <vector>

#include "../tinyrender.h"

#include "/code/LagrangePhysics_Alpha /Geometry/polygon_generator.h"
#include "/code/LagrangePhysics_Alpha /Geometry/polygon.h"
#include "/code/Utility/print.h"
#include "/code/Math/Containers/vec4.h"


struct Object {

  std::vector<vec2<double>> vertices;
  std::vector<int> indices;
};

int main(int argc, char *argv[]) {


  TinyRender render;

  std::vector<Object> objects;
  std::vector<mat4<double>> model_matrices;


  //create objects
  Object square;
  geometry::generator::Square(vec2<double>(0.5),&square.vertices);
  geometry::CalulatePolygonIndices(square.vertices,&square.indices);
  objects.push_back(square);
  //print::GeometryData(objects.begin(),objects.end());


  //create model matrix
  model_matrices.push_back(mat4<double>());
  

  //add color, create a default color, fix seg fault when color is noy init
  render.AddColor(0,square,vec4<float>(0.4,0.4,0.7,1.0)); 


  //init buffers
  render.InitPrimitiveBuffer(objects,model_matrices);



  while (render.run_flag) {

    render.DrawPrimitives(objects,model_matrices); 
  }
  
  

  std::cout<<"main\n";

  return 0;
}