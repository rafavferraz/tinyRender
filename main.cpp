#include "../../utility/print.h"

#include "window.h"
#include "event.h"
#include "camera.h"
#include "render.h"


int main() {

	Window window("Test Window",800,600);

	Event event_handler;

	Render render;


//main loop
	while (!glfwWindowShouldClose(window.window_ptr)) {

		event_handler.run(window.window_ptr,&render.camera);

		render.clear();

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


//render.h??
		//swap buffers
		glfwSwapBuffers(window.window_ptr);
	}

	return 0;
}
