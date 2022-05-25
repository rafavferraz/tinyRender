#include <random>

#include "../../utility/print.h"

#include "render.h"

int main() {

	Render<window::GLFW> render("Test Window",800,600,0,1600);

	std::mt19937_64 rng(std::random_device{}());
	std::uniform_real_distribution<double> distribution(-1.0,1.0);

	std::vector<glm::vec3> positions(100);

	auto setup = [&](){
		
		render.camera.setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

		for (auto& position : positions) {
			position = glm::vec3(distribution(rng),distribution(rng),0.0);
		}
	};

	auto update = [&](){

	};

	auto draw = [&]() {

		render.background(glm::vec4(0.0705f,0.0705f,0.0705f,1.0f));

		render.cameraBegin();

		render.pushMatrix();

			render.setColor(glm::vec4(0.435f, 0.6235f, 0.8117f, 0.7451f));
			
			for (uint64_t i = 0; i < positions.size(); ++i) {

				render.translate(positions.at(i));
				// render.drawSquare();
				render.drawCube();
			}

		render.popMatrix();

		render.setColor(glm::vec4(1.0f, 0.5f, 0.2f, 1.0f));

		render.drawTriangle();

		render.cameraEnd();
	};

	auto event = [&](){

		// if (glfwGetKey(window.window_ptr, GLFW_KEY_Z) == GLFW_PRESS) 
    //   ...
	};

	render.loop(setup,update,draw,event,true);

	return 0;
}






	// auto draw = [&]() {


	// 	std::mt19937_64 rng(std::random_device{}());
	// 	std::uniform_real_distribution<double> distribution(-10.0,10.0);

	// 	std::vector<glm::vec3> positions(10);

	// 	for (auto& i : positions)
	// 		i = glm::vec3(distribution(rng),distribution(rng),distribution(rng));



	// 	render.background(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

	// 	//model
	// 	glm::mat4 model_matrix = glm::mat4(1.0f);
	// 	model_matrix = glm::rotate(model_matrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// 	render.shader.setUniformMat4("model",model_matrix);

	// 	render.cameraBegin();

	// 	// render.drawTriangle();

	// 	render.pushMatrix();

	// 		// render.translate(glm::vec3(1.5,0.0,0.0));

	// 		// render.drawSquare();

	// 		// glm::vec3 position = glm::vec3(distribution(rng),distribution(rng),distribution(rng));

	// 		for (auto& i : positions) {
				
	// 			render.translate(i);
	// 			render.drawCube();

	// 		}

	// 		// render.drawTriangle();

	// 		render.drawCube();


	// 	render.popMatrix();

	// 	render.cameraEnd();
	// };