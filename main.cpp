#include "../../utility/print.h"

#include "window.h"
#include "event.h"
#include "camera.h"
#include "render.h"


int main() {

	Window window("Test Window",800,600);

	Render render;

	auto setup = [&](){

	};

	auto update = [&](){

	};

	auto draw = [&]() {

		render.background(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

		//model
		glm::mat4 model_matrix = glm::mat4(1.0f);
		model_matrix = glm::rotate(model_matrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		render.shader.setUniformMat4("model",model_matrix);

		render.cameraBegin();

		render.drawTriangle();

		render.pushMatrix();

			render.translate(glm::vec3(1.5,0.0,0.0));

			render.drawSquare();

			render.translate(glm::vec3(1.5,0.0,0.0));

			render.drawTriangle();

		render.popMatrix();

		render.cameraEnd();
	};

	auto event = [&](){

		// if (glfwGetKey(window.window_ptr, GLFW_KEY_Z) == GLFW_PRESS) 
    //   OUTPUT("Z pressed!!")
	};

	render.run(window,setup,update,draw,event);

	return 0;
}


