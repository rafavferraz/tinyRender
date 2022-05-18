#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <iostream>
#include <memory>

#include "/code/Math/Containers/mat4.h"
#include "/code/Math/LinearAlgebra/linear_algebra.h"

#include "buffer.h"

#define RENDER_FOV           45.0
#define RENDER_ASPECT_RATIO   1.0  // (float)screen_height / screen_width
#define RENDER_NEAR_PLANE     1.0
#define RENDER_FAR_PLANE    100.0

struct Shader {

  Shader(): program_id(0) {}
  ~Shader() {
    glUseProgram(0);
    glDeleteProgram(program_id);
  }

  GLuint program_id;
  std::string vertex_shader   = "/code/TinyRender/shaders/vertex.glsl";
  std::string fragment_shader = "/code/TinyRender/shaders/fragment.glsl";
};

struct ObjectShaderData {

  std::vector<vec3<float>> normal;
  std::vector<vec3<float>> texture;
  std::vector<vec4<float>> color;
};

template<typename Vertex>  //V is for vertex!!     <-------
struct Render {
 public:
  

  Render() {}
  ~Render();

  void Init();
  void Clear();
  void OpenGlInit();
  void SetBufferProgramIds();
  mat4<float> getPerspectiveMatrix();

  void InstallShaders(Shader &shader);
  std::string ReadShaderCode(std::string code);
  bool CheckShaderStatus(GLint shaderID);
  bool CheckProgramStatus(GLint programID);

  Buffer<Vertex> buffer_prim_;
  Buffer<Vertex> buffer_bv_;
  Buffer<Vertex> buffer_basic_;   // point/line buffer

  //model matrices storage, in case the engine does not use them for transforms
  std::vector<mat4<double>> prim_model_matrices;  //why double??
  std::vector<mat4<double>> basic_model_matrices;
  std::vector<mat4<double>> bv_model_matrices;

  //color, normals and textures info
  std::vector<ObjectShaderData> prim_shader_data;
  std::vector<ObjectShaderData> basic_shader_data;
  std::vector<ObjectShaderData> bv_shader_data;

  Shader shader;

//delete??
  float  alpha_;
  float  prim_alpha_;
  float  basic_alpha_;  
  float  bv_alpha_;  //maybe useful

};

template<typename Vertex>
 Render<Vertex>::~Render() {}

template<typename Vertex>
 void Render<Vertex>::Init() { 

  OpenGlInit();
  InstallShaders (shader); 
  SetBufferProgramIds();
}

template<typename Vertex>
 void Render<Vertex>::Clear() {

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  //glClearColor(0.153f, 0.156f, 0.133f, 1.0f);
  //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

template<typename Vertex>
 void Render<Vertex>::OpenGlInit() {
    
   // Initialize GLEW
   glewExperimental = GL_TRUE;
   glewInit();

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glLineWidth (2.0f);
   glEnable(GL_LINE_SMOOTH);

   //default winding order
   glEnable(GL_CULL_FACE);
   glFrontFace (GL_CCW);

   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glClear(GL_ACCUM_BUFFER_BIT);
}

template<typename Vertex>
 void Render<Vertex>::SetBufferProgramIds() {

  buffer_basic_.program_id_ = shader.program_id;
  buffer_prim_.program_id_ = shader.program_id;
  buffer_bv_.program_id_ = shader.program_id;
}

template<typename Vertex>
 mat4<float> Render<Vertex>::getPerspectiveMatrix() {

    return math::linear_algebra::Perspective ((float)RENDER_FOV,
                                              (float)RENDER_ASPECT_RATIO,
                                              (float)RENDER_NEAR_PLANE, 
                                              (float)RENDER_FAR_PLANE);
}

template<typename Vertex>
 void Render<Vertex>::InstallShaders(Shader &shader) {

  GLuint vertex_shaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shaderID = glCreateShader(GL_FRAGMENT_SHADER);

  const GLchar* adapter[1];

  std::string temp = ReadShaderCode (shader.vertex_shader);
  adapter[0] = temp.c_str();
  glShaderSource(vertex_shaderID, 1, adapter, 0);

  temp = ReadShaderCode (shader.fragment_shader);
  adapter[0] = temp.c_str();
  glShaderSource(fragment_shaderID, 1, adapter, 0);

  glCompileShader(vertex_shaderID);
  glCompileShader(fragment_shaderID);

  if (!CheckShaderStatus(vertex_shaderID) ||
      !CheckShaderStatus(fragment_shaderID)) {
    std::cout<<"Shader(s) failed to compile."<<std::endl;
    return;
  }

  shader.program_id = glCreateProgram();
  glAttachShader(shader.program_id, vertex_shaderID);
  glAttachShader(shader.program_id, fragment_shaderID);

  glLinkProgram(shader.program_id);

  if (!CheckProgramStatus (shader.program_id)) {
    std::cout<<"Shader(s) failed to attach."<<std::endl;
    return;
  }

  glDeleteShader(vertex_shaderID);
  glDeleteShader(fragment_shaderID);

  glUseProgram(shader.program_id);
}

template<typename Vertex> 
 std::string Render<Vertex>::ReadShaderCode(std::string code) {

    const char* fileName = code.c_str ();

    std::ifstream ifs;
    ifs.open(fileName);

    if ( !ifs.is_open())
    {
        std::cout<<"Shader text file failed to load: "<<fileName;
        exit(1);
    }

   return std::string ( (std::istreambuf_iterator<char>(ifs) ),
                        (std::istreambuf_iterator<char>()    ) );
}

template<typename Vertex>
 bool Render<Vertex>::CheckShaderStatus(GLint shaderID) {

  GLint compile_status;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_status);

  if (compile_status != GL_TRUE)
  {
    GLint infoLogLength;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    GLchar* buffer = new GLchar[infoLogLength];

    GLsizei buffer_size;
    glGetShaderInfoLog(shaderID, infoLogLength, &buffer_size, buffer);

    std::cout<<"Shader compilation error."<<std::endl;
    std::cout << buffer<<std::endl;

    delete [] buffer;

    return false;
  }
  return true;
}

template<typename Vertex>
 bool Render<Vertex>::CheckProgramStatus(GLint programID) {

    GLint link_status;
    glGetProgramiv(programID, GL_LINK_STATUS, &link_status);

    if (link_status != GL_TRUE)
    {
        GLint infoLogLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* buffer = new GLchar[infoLogLength];

        GLsizei buffer_size;
        glGetProgramInfoLog(programID, infoLogLength, &buffer_size, buffer);

        std::cout<<"Program link error."<<std::endl;
        std::cout << buffer<<std::endl;

        delete [] buffer;

        return false;
    }
    return true;
}


#endif // RENDER_H
