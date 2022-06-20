#pragma once

#include <numbers>
#include <map>
#include <utility>



#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct Object {

  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;

  unsigned int VAO_Instanced;
  unsigned int VBO_Instanced;
  unsigned int VBO_Instanced_position;
  unsigned int EBO_Instanced;

  std::vector<float> vertices;
  std::vector<unsigned int> indexes;

  void load();
  void draw() const;
};

struct Triangle : public Object {

  Triangle() {

    vertices = {  
     -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f 
    };

    load();
    loadInstanced();  
  }

  ~Triangle() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
  }

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }

  void loadInstanced() {

    static std::vector<glm::vec3> position = { glm::vec3(0.0,0.0,0.0) };
    loadInstanced(position);
  }

  void loadInstanced(const std::vector<glm::vec3>& position) {
    
    glGenVertexArrays(1,&VAO_Instanced);
    glGenBuffers(1,&VBO_Instanced);
    glGenBuffers(1,&VBO_Instanced_position);

    glBindVertexArray(VAO_Instanced);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //instance buffer loading
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glBufferData(GL_ARRAY_BUFFER,position.size() * sizeof(glm::vec3), 
      &position[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);	
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
  }

  void draw() const {

    glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
  }

  void drawInstanced(const int& count) const {

    glBindVertexArray(VAO_Instanced);
    glDrawArraysInstanced(GL_TRIANGLES,0,3,count);
    glBindVertexArray(0);
  }
};

struct Square : public Object {

  Square() {

    vertices = {  
      0.5f,  0.5f, 0.0f,  
      0.5f, -0.5f, 0.0f,  
     -0.5f, -0.5f, 0.0f,  
     -0.5f,  0.5f, 0.0f  
    };

    indexes = {
      0, 1, 3,  
      1, 2, 3 
    };

    load();
    loadInstanced();  
  }

  ~Square() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);

    glDeleteVertexArrays(1,&VAO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced_position);
	  glDeleteBuffers(1,&EBO_Instanced);
  }

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }

  void loadInstanced() {

    static std::vector<glm::vec3> position = { glm::vec3(0.0,0.0,0.0) };
    loadInstanced(position);
  }

  void loadInstanced(const std::vector<glm::vec3>& position) {

    glGenVertexArrays(1,&VAO_Instanced);
    glGenBuffers(1,&VBO_Instanced);
    glGenBuffers(1,&VBO_Instanced_position);
    glGenBuffers(1,&EBO_Instanced);

    glBindVertexArray(VAO_Instanced);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Instanced);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //instance buffer loading
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glBufferData(GL_ARRAY_BUFFER,position.size() * sizeof(glm::vec3), 
      &position[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);	
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
  }

  void draw() const {  

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void drawInstanced(const int& count) const {

    glBindVertexArray(VAO_Instanced);
    glDrawElementsInstanced(GL_TRIANGLES,6,GL_UNSIGNED_INT,0,count);
    glBindVertexArray(0);
  }
};

struct Circle : public Object {

  Circle() {

    generateVertices();
    generateIndices();

    load();
    loadInstanced();  
  }

  ~Circle() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);

    glDeleteVertexArrays(1,&VAO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced_position);
	  glDeleteBuffers(1,&EBO_Instanced);
  }

  void generateVertices(const int& number_vertices = 32) {

    vertices.clear();

    int min = std::max(number_vertices,3);
    float step = (2.0 * std::numbers::pi) / min;

    for (int i = 0; i < min; ++i) {

      vertices.push_back(std::cos(i * step));
      vertices.push_back(std::sin(i * step));
      vertices.push_back(0.0f);
    }
  }

  void generateIndices(const int& number_vertices = 32) {

    indexes.clear();

    int number_indices = std::max(1,number_vertices - 1);
    
    for (int i = 1, j = 2; i < number_indices; ++i, ++j) {

      indexes.push_back(0);
      indexes.push_back(i);
      indexes.push_back(j);
    }
  }

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }

  void loadInstanced() {

    static std::vector<glm::vec3> position = { glm::vec3(0.0,0.0,0.0) };
    loadInstanced(position);
  }

  void loadInstanced(const std::vector<glm::vec3>& position) {

    glGenVertexArrays(1,&VAO_Instanced);
    glGenBuffers(1,&VBO_Instanced);
    glGenBuffers(1,&EBO_Instanced);

    glBindVertexArray(VAO_Instanced);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO_Instanced);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //instance buffer loading
    glGenBuffers(1,&VBO_Instanced_position);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glBufferData(GL_ARRAY_BUFFER,position.size() * sizeof(glm::vec3), 
      &position[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);	
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
  }

  void draw() const {

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void drawInstanced(const int& count) const {

    glBindVertexArray(VAO_Instanced);
    glDrawElementsInstanced(GL_TRIANGLES,indexes.size(),GL_UNSIGNED_INT,0,count);
    glBindVertexArray(0);
  }
};

struct Cube : public Object {

  Cube() {

    vertices = {  
      0.5, 0.5, -0.5,
     -0.5, 0.5, -0.5,
     -0.5, 0.5, 0.5,
      0.5, 0.5, 0.5,
      0.5, -0.5, -0.5,
     -0.5, -0.5, -0.5,
     -0.5, -0.5, 0.5,
      0.5, -0.5, 0.5
    };

    indexes = {
      0, 1, 2, 
      0, 2, 3, 
      0, 4, 5, 
      0, 5, 1, 
      1, 5, 6, 
      1, 6, 2, 
      2, 6, 7, 
      2, 7, 3, 
      3, 7, 4, 
      3, 4, 0, 
      4, 7, 6, 
      4, 6, 5 
    };

    load();
    loadInstanced();  
  }

  ~Cube() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);

    glDeleteVertexArrays(1,&VAO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced_position);
	  glDeleteBuffers(1,&EBO_Instanced);
  }

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }

  void loadInstanced() {

    static std::vector<glm::vec3> position = { glm::vec3(0.0,0.0,0.0) };
    loadInstanced(position);
  }

  void loadInstanced(const std::vector<glm::vec3>& position) {
    
    glGenVertexArrays(1,&VAO_Instanced);
    glGenBuffers(1,&VBO_Instanced);
    glGenBuffers(1,&VBO_Instanced_position);
    glGenBuffers(1,&EBO_Instanced);

    glBindVertexArray(VAO_Instanced);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Instanced);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //instance buffer loading
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glBufferData(GL_ARRAY_BUFFER,position.size() * sizeof(glm::vec3), 
      &position[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);	
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
  }

  void draw() const {

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void drawInstanced(const int& count) const {

    glBindVertexArray(VAO_Instanced);
    glDrawElementsInstanced(GL_TRIANGLES,36,GL_UNSIGNED_INT,0,count);
    glBindVertexArray(0);
  }
};  

// //sphere tessalation
// http://www.songho.ca/opengl/gl_sphere.html
// https://prideout.net/blog/old/blog/index.html@p=48.html
// https://observablehq.com/@mourner/fast-icosphere-mesh
// https://schneide.blog/2016/07/15/generating-an-icosphere-in-c/

struct Sphere : public Object {

  Sphere() {

    generate();

    load();
    loadInstanced();  
  }

  ~Sphere() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);

    glDeleteVertexArrays(1,&VAO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced_position);
	  glDeleteBuffers(1,&EBO_Instanced);
  }

  using Index = int;

  struct Triangle {
    Index vertex[3];
  };

  // Credit: code based on the following website:
  // https://schneide.blog/2016/07/15/generating-an-icosphere-in-c/
  void generate(const int& subdivisions = 2) {

    vertices.clear();
    indexes.clear();

    using TriangleList = std::vector<Triangle>;
    using VertexList = std::vector<glm::vec3>;

    const float X = 0.525731112119133606f;
    const float Z = 0.850650808352039932f;
    const float N = 0.f;

    const VertexList icosahedron_vertices = {
      {-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
      {N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
      {Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
    };

    const TriangleList icosahedron_triangles = {
      {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
      {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
      {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
      {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
    };

    //part 1
    using Lookup = std::map<std::pair<Index, Index>, Index>;
    
    auto vertex_for_edge = [&](Lookup& lookup,
      VertexList& vertices_local, Index first, Index second) {

      Lookup::key_type key(first, second);
      if (key.first>key.second)
        std::swap(key.first, key.second);
    
      auto inserted=lookup.insert({key, vertices_local.size()});
      if (inserted.second)
      {
        auto& edge0=vertices_local[first];
        auto& edge1=vertices_local[second];
        auto point=normalize(edge0+edge1);
        vertices_local.push_back(point);
      }
    
      return inserted.first->second;
    };

    //part 2
    auto subdivide = [&](VertexList& vertices_local, TriangleList triangles) {
      
      Lookup lookup;
      TriangleList result;
    
      for (auto&& each:triangles)
      {
        std::array<Index, 3> mid;
        for (int edge=0; edge<3; ++edge)
        {
          mid[edge]=vertex_for_edge(lookup, vertices_local,
            each.vertex[edge], each.vertex[(edge+1)%3]);
        }
    
        result.push_back({each.vertex[0], mid[0], mid[2]});
        result.push_back({each.vertex[1], mid[1], mid[0]});
        result.push_back({each.vertex[2], mid[2], mid[1]});
        result.push_back({mid[0], mid[1], mid[2]});
      }
    
      return result;
    };
    
    using IndexedMesh = std::pair<VertexList, TriangleList>;
    
    auto make_icosphere = [&](int number_subdivisions) {

      VertexList vertices_local = icosahedron_vertices;
      TriangleList triangles = icosahedron_triangles;
    
      for (int i=0; i<number_subdivisions; ++i) {
        triangles = subdivide(vertices_local, triangles);
      }
    
      return IndexedMesh{vertices_local, triangles};
    };

    auto mesh = make_icosphere(subdivisions);

    auto [ mesh_vertices, mesh_triangles ]  = mesh;

    //vertices
    for (unsigned int i = 0; i < mesh_vertices.size(); ++i) {
      
      vertices.push_back(mesh_vertices.at(i).x);
      vertices.push_back(mesh_vertices.at(i).y);
      vertices.push_back(mesh_vertices.at(i).z);
    }

    //indexes
    for (unsigned int i = 0; i < mesh_triangles.size(); ++i) {
      
      indexes.push_back(mesh_triangles.at(i).vertex[0]);
      indexes.push_back(mesh_triangles.at(i).vertex[1]);
      indexes.push_back(mesh_triangles.at(i).vertex[2]);
    }
  }

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }

  void loadInstanced() {

    static std::vector<glm::vec3> position = { glm::vec3(0.0,0.0,0.0) };
    loadInstanced(position);
  }

  void loadInstanced(const std::vector<glm::vec3>& position) {

    glGenVertexArrays(1,&VAO_Instanced);
    glGenBuffers(1,&VBO_Instanced);
    glGenBuffers(1,&EBO_Instanced);

    glBindVertexArray(VAO_Instanced);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO_Instanced);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //instance buffer loading
    glGenBuffers(1,&VBO_Instanced_position);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glBufferData(GL_ARRAY_BUFFER,position.size() * sizeof(glm::vec3), 
      &position[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);	
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
  }

  void draw() const {
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,indexes.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
  }

  void drawInstanced(const int& count) const {

    glBindVertexArray(VAO_Instanced);
    glDrawElementsInstanced(GL_TRIANGLES,indexes.size(),GL_UNSIGNED_INT,0,count);
    glBindVertexArray(0);
  }
};

struct Cone : public Object {

  Cone() {

    generateVertices();
    generateIndices();

    load();
    loadInstanced();  
  }

  ~Cone() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);

    glDeleteVertexArrays(1,&VAO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced_position);
	  glDeleteBuffers(1,&EBO_Instanced);
  }

  void generateVertices(const int& number_vertices = 32) {

    vertices.clear();

    int min = std::max(number_vertices,3);
    float step = (2.0 * std::numbers::pi) / min;

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(1.0f);

    for (int i = 0; i < min; ++i) {

      vertices.push_back(std::cos(i * step));
      vertices.push_back(std::sin(i * step));
      vertices.push_back(0.0f);
    }
  }

  void generateIndices(const int& number_vertices = 32) {

    indexes.clear();

    //cone
    for (int i = 1, j = 2; i < number_vertices; ++i, ++j) {

      indexes.push_back(0);
      indexes.push_back(i);
      indexes.push_back(j);
    }

      indexes.push_back(0);
      indexes.push_back(number_vertices);
      indexes.push_back(1);

    //circle
    for (int i = 1, j = 2; i < number_vertices; ++i, ++j) {

      indexes.push_back(1);
      indexes.push_back(i);
      indexes.push_back(j);
    }
  }

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }

  void loadInstanced() {

    static std::vector<glm::vec3> position = { glm::vec3(0.0,0.0,0.0) };
    loadInstanced(position);
  }

  void loadInstanced(const std::vector<glm::vec3>& position) {

    glGenVertexArrays(1,&VAO_Instanced);
    glGenBuffers(1,&VBO_Instanced);
    glGenBuffers(1,&EBO_Instanced);

    glBindVertexArray(VAO_Instanced);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO_Instanced);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //instance buffer loading
    glGenBuffers(1,&VBO_Instanced_position);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glBufferData(GL_ARRAY_BUFFER,position.size() * sizeof(glm::vec3), 
      &position[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);	
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
  }

  void draw() const {

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void drawInstanced(const int& count) const {

    glBindVertexArray(VAO_Instanced);
    glDrawElementsInstanced(GL_TRIANGLES,indexes.size(),GL_UNSIGNED_INT,0,count);
    glBindVertexArray(0);
  }
};

struct Cylinder : public Object {

  Cylinder() {

    generateVertices();
    generateIndices();

    load();
    loadInstanced();  
  }

  ~Cylinder() {

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
	  glDeleteBuffers(1,&EBO);

    glDeleteVertexArrays(1,&VAO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced);
    glDeleteBuffers(1,&VBO_Instanced_position);
	  glDeleteBuffers(1,&EBO_Instanced);
  }

  void generateVertices(const int& number_vertices = 32) {

    vertices.clear();

    int min = std::max(number_vertices,3);
    float step = (2.0 * std::numbers::pi) / min;

    for (int i = 0; i < min; ++i) {

      vertices.push_back(std::cos(i * step));
      vertices.push_back(std::sin(i * step));
      vertices.push_back(0.0f);
    }

    for (int i = 0; i < min; ++i) {

      vertices.push_back(std::cos(i * step));
      vertices.push_back(std::sin(i * step));
      vertices.push_back(1.0f);
    }
  }

  void generateIndices(const int& number_vertices = 32) {

    indexes.clear();

    int index_a_end = (vertices.size() / 2) / 3 - 1;

    int index_b_start = index_a_end + 1;
    int index_b_end = vertices.size() / 3 - 1;

    //lower circle
    for (int i = 1, j = 2; i < index_a_end; ++i, ++j) {

      indexes.push_back(0);
      indexes.push_back(i);
      indexes.push_back(j);
    }

    //upper circle
    for (int i = 1 + index_b_start, j = 2 + index_b_start; i < index_b_end; ++i, ++j) {

      indexes.push_back(0 + index_b_start);
      indexes.push_back(i);
      indexes.push_back(j);
    }

    //cylinder walls tessalation
   for (int i = 0; i < index_b_start; ++i) {

      indexes.push_back(index_b_start + i);
      indexes.push_back(i);
      indexes.push_back(i + 1);

    }

    indexes.back() = 0;

   for (int i = 0; i < index_b_start; ++i) {

      indexes.push_back(index_b_start + i);
      indexes.push_back(i + 1);
      indexes.push_back(index_b_start + i + 1);
    }
    
    indexes.back() = 0;
  }

  void load() {

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
  }

  void loadInstanced() {

    static std::vector<glm::vec3> position = { glm::vec3(0.0,0.0,0.0) };
    loadInstanced(position);
  }

  void loadInstanced(const std::vector<glm::vec3>& position) {

    glGenVertexArrays(1,&VAO_Instanced);
    glGenBuffers(1,&VBO_Instanced);
    glGenBuffers(1,&EBO_Instanced);

    glBindVertexArray(VAO_Instanced);

    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),
      &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO_Instanced);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), 
      &indexes[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //instance buffer loading
    glGenBuffers(1,&VBO_Instanced_position);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glBufferData(GL_ARRAY_BUFFER,position.size() * sizeof(glm::vec3), 
      &position[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_Instanced_position);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);	
    glVertexAttribDivisor(1, 1);  

    glBindVertexArray(0);
  }

  void draw() const {

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }

  void drawInstanced(const int& count) const {

    glBindVertexArray(VAO_Instanced);
    glDrawElementsInstanced(GL_TRIANGLES,indexes.size(),GL_UNSIGNED_INT,0,count);
    glBindVertexArray(0);
  }
};