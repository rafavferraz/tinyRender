#include "../../utility/print.h"

#include "dependencies/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "window.h"
#include "event.h"
#include "camera.h"


// //render.h
// 	float vertices[] = {
// 			0.5f,  0.5f, 0.0f,  // top right
// 			0.5f, -0.5f, 0.0f,  // bottom right
// 			-0.5f, -0.5f, 0.0f,  // bottom left
// 			-0.5f,  0.5f, 0.0f   // top left 
// 	};

// 	unsigned int indices[] = {  // note that we start from 0!
// 			0, 1, 3,   // first triangle
// 			1, 2, 3    // second triangle
// 	};
// //render.h


int main() {

	Window window("Test Window",800,600);

	Shader shader("./shader.vert","./shader.frag");

	Event event_handler;

	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));


	float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
				0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
			glm::vec3( 0.0f,  0.0f,  0.0f), 
			glm::vec3( 2.0f,  5.0f, -15.0f), 
			glm::vec3(-1.5f, -2.2f, -2.5f),  
			glm::vec3(-3.8f, -2.0f, -12.3f),  
			glm::vec3( 2.4f, -0.4f, -3.5f),  
			glm::vec3(-1.7f,  3.0f, -7.5f),  
			glm::vec3( 1.3f, -2.0f, -2.5f),  
			glm::vec3( 1.5f,  2.0f, -2.5f), 
			glm::vec3( 1.5f,  0.2f, -1.5f), 
			glm::vec3(-1.3f,  1.0f, -1.5f)  
	};


//Render.h
	unsigned int VBO, VAO;
	// unsigned int EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// //EBO
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	glEnable(GL_DEPTH_TEST); 
//Render.h

//main loop
	while (!glfwWindowShouldClose(window.window_ptr)) {

		event_handler.run(window.window_ptr,&camera);

		shader.use();

//render.h
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// //transform
		// glm::mat4 transform = glm::mat4(1.0f);
		// transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));

		// shader.setUniformMat4("transform",transform);


		//model
		glm::mat4 model_matrix = glm::mat4(1.0f);
		model_matrix = glm::rotate(model_matrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		//view
		// glm::mat4 view_matrix = glm::mat4(1.0f);
		// view_matrix = glm::translate(view_matrix, glm::vec3(0.0f, 0.0f, -3.0f)); 


		glm::mat4 view_matrix = camera.GetViewMatrix();


		//projection
		glm::mat4 projection_matrix;
		projection_matrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		
		shader.setUniformMat4("model",model_matrix);
		shader.setUniformMat4("view",view_matrix);
		shader.setUniformMat4("projection",projection_matrix);

		glBindVertexArray(VAO);

		// glDrawArrays(GL_TRIANGLES, 0, 36);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		for(unsigned int i = 0; i < 10; i++) {

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i; 
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			shader.setUniformMat4("model",model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//swap buffers
		glfwSwapBuffers(window.window_ptr);
//render.h

	}

//Render.h
	//delete shader objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// glDeleteBuffers(1, &EBO);
//Render.h

	shader.deleteShader();

	window.terminate();

	return 0;
}
