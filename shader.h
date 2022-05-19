#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

#include "dependencies/glad/include/glad/glad.h"


struct Shader {

  Shader() {}
  Shader(const std::string& vertex_path, const std::string& fragment_path) {

    auto [ vertex_code, fragment_code ] = read(vertex_path,fragment_path);
    compile(vertex_code.c_str(),fragment_code.c_str());
  }

  ~Shader() {
    // glDeleteProgram(shader_id);  
  }

  void deleteShader() {
    glDeleteProgram(shader_id);  
  }

  std::pair<std::string,std::string> read(const std::string& vertex_path, 
                                          const std::string& fragment_path) {

    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vertex_shader_file;
    std::ifstream fragment_shader_file;

    //ensure ifstream objects can throw exceptions:
    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {

      vertex_shader_file.open(vertex_path.c_str());
      fragment_shader_file.open(fragment_path.c_str());

      std::stringstream vertex_shader_stream;
      std::stringstream fragment_shader_stream;

      vertex_shader_stream << vertex_shader_file.rdbuf();
      fragment_shader_stream << fragment_shader_file.rdbuf();	

      vertex_shader_file.close();
      fragment_shader_file.close();

      vertex_code = vertex_shader_stream.str();
      fragment_code = fragment_shader_stream.str();		

    } catch(std::ifstream::failure& e) {
        std::cout << "Error @ reading shader file." << std::endl;
    }

    return std::make_pair(vertex_code,fragment_code); 
  }

  void compile(const std::string& vertex_code, const std::string& fragment_code) {

    const char* vertex_shader_code = vertex_code.c_str();
    const char* fragment_shader_code = fragment_code.c_str();

    //vertex Shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex);

    checkErrors(vertex,"vertex shader");

    //fragment shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment);

    checkErrors(fragment,"fragment shader");

    //link shader program
    shader_id = glCreateProgram();
    glAttachShader(shader_id,vertex);
    glAttachShader(shader_id,fragment);
    glLinkProgram(shader_id);

    checkErrors(shader_id,"linker");

    //delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  void checkErrors(unsigned int& shader, const std::string& shader_type = "") {

    int success;
    char infoLog[512];
      
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success) {

      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "Error @ " << shader_type << " compilation." << std::endl << infoLog << std::endl;
    };
  }

  void use() {
    glUseProgram(shader_id);
  }

  void setUniformBool(const std::string &name, const bool& value) const {         
    glUniform1i(glGetUniformLocation(shader_id, name.c_str()), (int)value); 
  }

  void setUniformInt(const std::string &name, const int& value) const { 
    glUniform1i(glGetUniformLocation(shader_id, name.c_str()), value); 
  }
  
  void setUniformFloat(const std::string &name, const float& value) const { 
    glUniform1f(glGetUniformLocation(shader_id, name.c_str()), value); 
  } 

  void setUniformMat4(const std::string &name, const glm::mat4& value) const { 
		glUniformMatrix4fv(glGetUniformLocation(shader_id,name.c_str()),1,GL_FALSE,glm::value_ptr(value));
  } 

  unsigned int shader_id;

};


