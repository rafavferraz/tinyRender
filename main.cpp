#include <random>

#include "../../utility/print.h"

#include "render.h"


int main() {

	Render<window::GLFW> render("Test Window",800,600,0,1600);


	auto setup = [&](){
		
		render.camera.setPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	};

	auto update = [&](){

	};

	auto draw = [&]() {

		render.background(glm::vec4(0.0705f,0.0705f,0.0705f,1.0f));

		render.cameraBegin();

		render.pushMatrix();

			render.setColor(glm::vec4(1.0f, 0.5f, 0.2f, 1.0f));

			render.drawSquare();

		render.popMatrix();

		render.cameraEnd();
	};

	auto event = [&](){


	};

	render.loop(setup,update,draw,event,true);

	return 0;
}




























// int main() {

// 	Render<window::GLFW> render("Test Window",800,600,0,1600);

// 	// std::mt19937_64 rng(std::random_device{}());
// 	// std::uniform_real_distribution<double> distribution(-1.0,1.0);

// 	// std::vector<glm::vec3> positions(100);

// 	auto setup = [&](){
		
// 		render.camera.setPosition(glm::vec3(0.0f, 0.0f, 5.0f));

// 		// for (auto& position : positions) {
// 		// 	position = glm::vec3(distribution(rng),distribution(rng),0.0);
// 		// }
// 	};

// 	auto update = [&](){

// 	};

// 	auto draw = [&]() {

// 		render.background(glm::vec4(0.0705f,0.0705f,0.0705f,1.0f));

// 		render.cameraBegin();

// 		render.pushMatrix();

			
// 			render.setColor(glm::vec4(1.0f, 0.5f, 0.2f, 1.0f));

// 			render.drawSquare();

// 			// render.setColor(glm::vec4(0.435f, 0.6235f, 0.8117f, 0.7451f));

// 			// for (uint64_t i = 0; i < positions.size(); ++i) {

// 			// 	render.translate(positions.at(i));
// 			// 	// render.drawSquare();
// 			// 	render.drawCube();
// 			// }

// 		render.popMatrix();

// 		// render.setColor(glm::vec4(1.0f, 0.5f, 0.2f, 1.0f));

// 		// render.drawTriangle();

// 		render.cameraEnd();
// 	};

// 	auto event = [&](){

// 		// if (glfwGetKey(window.window_ptr, GLFW_KEY_Z) == GLFW_PRESS) 
//     //   ...
// 	};

// 	render.loop(setup,update,draw,event,true);

// 	return 0;
// }