#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>
#include <memory>

#include <GL/glew.h>

#include "/code/Math/Containers/vec2.h"
#include "/code/Math/Containers/vec3.h"
#include "/code/Math/Containers/vec4.h"
#include "/code/Math/Containers/mat4.h"
#include "/code/Utility/print.h"


template<typename V_float> //either vec2_float or vec3_float
struct Buffer {

  Buffer(): program_id_(0), vbo_vertex(0), vbo_model_matrix(0), vbo_color(0),
            vao(0) {}
  ~Buffer() {

     glUseProgram(0);
     glDeleteBuffers(1, &vbo_vertex);
     glDeleteBuffers(1, &vbo_model_matrix);
     glDeleteBuffers(1, &vbo_color);
     glDeleteVertexArrays(1, &vao);
  }

  GLuint program_id_;

  GLuint vbo_vertex; //vertex
  GLuint vbo_model_matrix;
  GLuint vbo_color;
  GLuint ebo;  //element buffer object
  GLuint vao;

  GLuint uniform_projection_matrix;


//WTF??
  //WTF??
  //WTF?? WHY HEREEEE??
  std::vector<V_float>     vertices;
  std::vector<int>         indices;
  std::vector<vec4<float>> color;
  std::vector<mat4<float>> model_matrix;


  std::vector<int>  instanced_index;


  void GenerateBuffers();

  template<typename InputIt1, typename InputIt2, typename InputIt3>
   void InitAllBuffers (InputIt1 first1, InputIt1 last1,
                        InputIt2 first2, InputIt2 last2,
                        InputIt3 first3, InputIt3 last3);

  template<typename InputIt> void UpdateVertexBuffer(const InputIt first,
                                                     const InputIt last);
  template<typename InputIt> void UpdateElementBuffer(const InputIt first,
                                                      const InputIt last);
  template<typename InputIt> void UpdateColorBuffer(const InputIt first,
                                                    const InputIt last);
  template<typename InputIt> void UpdateModelMatrixBuffer(const InputIt first,
                                                          const InputIt last
                                                          );
  template<typename InputIt> void UpdateAlphaUniform(const InputIt first,
                                                     const InputIt last);
  
  template<typename InputIt> void Draw (const mat4<float>& projection_matrix, 
                                        InputIt first, InputIt last);

  void DrawInstanced(); //takes advantage that some objects have the same shape

  /*
   * how to select between instanced and normal?
   * maybe compare number of elements to number of shapes?
   * instances = [ 1 10; 2 1; 3 30; ..] -> [10 1 30]
   * for points an lines will be always:
   * [10] or [1000] ->they are all points, just the transform is different
  */
};

template<typename V_float> template<typename InputIt> inline
 void Buffer<V_float>::Draw (const mat4<float>& projection_matrix, 
                            const InputIt first, const InputIt last) {

  glUseProgram(program_id_);
  glBindVertexArray(vao);

  //projection matrix
  glUniformMatrix4fv(uniform_projection_matrix, 1, GL_FALSE,
                     (float*)&projection_matrix);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_model_matrix);

  int index(0), size(0), offset(0), iteration(0);
  for (InputIt it = first; it != last; ++it, iteration++) {

    size = (*it).indices.size();

    glBufferData(GL_ARRAY_BUFFER,  sizeof(mat4<float>),
                 &model_matrix[iteration],
                 GL_DYNAMIC_DRAW);

    glDrawElementsBaseVertex (GL_TRIANGLES, size, GL_UNSIGNED_INT,
                              (void*)(sizeof(int)*offset),
                              index);
    
    index += (*it).vertices.size();
    offset += size;
   }

  glBindVertexArray(0);
  glUseProgram(0);
}

template<typename V_float>
 template<typename InputIt1, typename InputIt2, typename InputIt3> inline
  void Buffer<V_float>::InitAllBuffers (InputIt1 first1, InputIt1 last1,
                                        InputIt2 first2, InputIt2 last2,
                                        InputIt3 first3, InputIt3 last3) {

   UpdateVertexBuffer(first1,last1);
   UpdateElementBuffer(first1,last1);
   UpdateColorBuffer(first2,last2);
   UpdateModelMatrixBuffer(first3,last3);
}

template<typename V_float> template<typename InputIt> inline
void Buffer<V_float>::UpdateVertexBuffer (InputIt first, InputIt last) {

  glUseProgram(program_id_);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);

  vertices.clear();

  for (InputIt it = first; it != last; ++it) {
    for (auto it2 = (*it).vertices.begin(); it2 != (*it).vertices.end();++it2)
    {
      V_float vec;
      vec = *it2;
      vertices.push_back (vec);
    }
  }

  glBufferData(GL_ARRAY_BUFFER, vertices.size () * sizeof(vec3<float>),
               &vertices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
  glUseProgram(0);
}

template<typename V_float> template<typename InputIt> inline
void Buffer<V_float>::UpdateElementBuffer (InputIt first, InputIt last) {

  glUseProgram(program_id_);
  glBindVertexArray(vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  indices.clear();

  //int index_counter(0);
  for (InputIt it = first; it != last; ++it) {

    for (auto it2 = (*it).indices.begin(); it2 != (*it).indices.end(); ++it2)
    {
      indices.push_back (*it2);// + index_counter);
    }
    //index_counter += (*it).indices_.size()/3 + 2;
  }

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size () * sizeof(int),
               &indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
  glUseProgram(0);
}

template<typename V_float> template<typename InputIt> inline
void Buffer<V_float>::UpdateColorBuffer (InputIt first, InputIt last) {

  glUseProgram(program_id_);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_color);

  color.clear();

  for (InputIt it = first; it != last; ++it) {
    for (auto it2 = (*it).color.begin(); it2 != (*it).color.end(); ++it2) {
      color.push_back (*it2);
    }
  }

  glBufferData(GL_ARRAY_BUFFER, color.size () * sizeof(vec4<float>), &color[0],
               GL_STATIC_DRAW);

  glBindVertexArray(0);
  glUseProgram(0);
}

template<typename V_float> template<typename InputIt> inline
void Buffer<V_float>::UpdateModelMatrixBuffer (InputIt first, InputIt last) {

  glUseProgram(program_id_);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_model_matrix);

  model_matrix.clear();

  for (InputIt it = first; it != last; ++it) {
      mat4<float> mat;
      mat = *it;
      model_matrix.push_back (mat);
  }

 // glBufferData(GL_ARRAY_BUFFER, model_matrix.size () * sizeof(mat4),
 //              &model_matrix[0], GL_DYNAMIC_DRAW);

  glBindVertexArray(0);
  glUseProgram(0);
}

template<typename V_float>
inline void Buffer<V_float>::GenerateBuffers () {

  glUseProgram(program_id_);

  //VAO
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //Position
  glGenBuffers(1, &vbo_vertex);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);
  glEnableVertexAttribArray(0);

  //stride = -2*sizeof(V)+24
  //offset, stride
  glVertexAttribPointer(0, sizeof(V_float)/4, GL_FLOAT, GL_FALSE,
                        24-2*sizeof(V_float),0);
  //glVertexAttribPointer(0, 2 , GL_FLOAT, GL_FALSE, sizeof(V) ,0);

  //Index Buffer
  glGenBuffers(1,&ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  //Model_matrix
  glGenBuffers(1, &vbo_model_matrix);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_model_matrix);

  GLuint vec4size = sizeof(vec4<float>);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * vec4size, 
                        (GLvoid*)(intptr_t)0);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4size,
                        (GLvoid*)(intptr_t)(vec4size));

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4size,
                        (GLvoid*)(intptr_t)(2 * vec4size));

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4size,
                        (GLvoid*)(intptr_t)(3 * vec4size));

  glVertexAttribDivisor(1, 1);
  glVertexAttribDivisor(2, 1);
  glVertexAttribDivisor(3, 1);
  glVertexAttribDivisor(4, 1);

  //color
  glGenBuffers(1, &vbo_color);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_color);

  glEnableVertexAttribArray(5);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(vec4<float>),
                        (GLvoid*)0);

  //Uniforms

  //projection matrix
  uniform_projection_matrix = glGetUniformLocation(program_id_,
                                                   "projection_matrix");

  glBindVertexArray(0);
  glUseProgram(0);
}


#endif // BUFFER_H
