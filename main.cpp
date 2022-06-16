#include <random>
#include <chrono>
#include <thread>

#include "../../utility/print.h"

#include "render.h"


int main() {

	Render<window::GLFW> render("Test Window",1200,900,0,1600);

	std::mt19937_64 rng(std::random_device{}());
	std::uniform_real_distribution<float> distribution(-10.0,10.0);

	// const int N = 1000;//000;//30'000;
	std::vector<glm::vec3> position;

	auto setup = [&](){
		
		render.camera.setPosition(glm::vec3(0.0f,0.0f,5.0f));

		// for (int i = 0; i < N; ++i) {

		// 	float x = distribution(rng);
		// 	float y = distribution(rng);

		// 	position.push_back(glm::vec3(x,y,0.0f));
		// }

		position.push_back(glm::vec3(0.0,0.0,0.0));
		position.push_back(glm::vec3(1.0,0.0,0.0));
		position.push_back(glm::vec3(0.0,1.0,0.0));
		position.push_back(glm::vec3(1.0,1.0,0.0));

		// render.loadTriangleInstanced(position);
		// render.loadRectangleInstanced(position);
		render.loadCircleInstanced(position);

	};

	auto update = [&](){

		// std::this_thread::sleep_for(std::chrono::nanoseconds(10));
    // std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
	};

	auto draw = [&]() {

		render.background(glm::vec4(0.0705f,0.0705f,0.0705f,1.0f));

		render.cameraBegin();

		render.drawAxis();

    render.pushMatrix();

			render.setColor(glm::vec4(1.0f,0.0f,0.0f,0.4f));

			render.drawTriangle(glm::vec3(0.0,0.0,0.0));
			render.drawTriangle(glm::vec3(1.0,0.0,0.0));
			render.drawTriangle(glm::vec3(0.0,1.0,0.0));
			render.drawTriangle(glm::vec3(1.0,1.0,0.0));
			
			render.setColor(glm::vec4(1.0f,0.5f,0.2f,0.6f));

			// for (int i = 0; i < position.size(); ++i) {

			// 	// render.drawTriangle(position.at(i));

			// 	render.setColor(glm::vec4(0.5f * i,0.5f * i,0.2f * i,0.4f));
			// 	render.drawRectangle(position.at(i),1.0,1.0);
			// 	// render.drawCircle(position.at(i),0.5);
			// }

			// render.drawTriangleInstanced(position.size(),1.0,1.0);
			// render.drawRectangleInstanced(position.size(),1.0,1.0);
			render.drawCircleInstanced(position.size(),0.5);


		render.popMatrix();

		render.cameraEnd();
	};

	auto event = [&](){

	};

	render.loop(setup,update,draw,event,true);

	return 0;
}







































		// auto point_a = glm::vec3(distribution(rng),distribution(rng),0.0);
		// auto point_b = glm::vec3(distribution(rng),distribution(rng),0.0);

		// auto point_a = glm::vec3(13.0,2.0,0.0);
		// auto point_b = glm::vec3(3.0,6.0,0.0);


// //anchor spots
// 		render.setColor(glm::vec4(1.0f,0.0f,0.0f,1.0f));

// 		render.drawTriangle(point_a);
// 		render.drawTriangle(point_b);

// //render
// 		render.pushMatrix();

// 			render.setColor(glm::vec4(1.0f,0.5f,0.2f,0.6f));
// 			render.drawLine(point_a,point_b);








			// render.setColor(glm::vec4(1.0f,0.5f,0.2f,1.0f));

			// // render.scale(glm::vec3(2.0,2.0,1.0));
			// // render.rotate(glm::radians(45.0),glm::vec3(0.0,0.0,1.0));
			// // render.translate(glm::vec3(1.0,1.0,0.0));

			// // render.drawRectangle(glm::vec3(0.0,0.0,0.0),1.0,2.0,false);

			// // render.drawRectangle(glm::vec3(0.0,0.0,0.0),glm::radians(45.0),1.0,1.0,true);

			// glm::mat4 transform = glm::mat4(1.0f);

      // transform = glm::translate(transform,glm::vec3(0.25,0.25,0.0));
      // transform = glm::rotate(transform,(float)glm::radians(45.0),glm::vec3(0.0,0.0,1.0));

			// // OUTPUT(glm::to_string(transform))
			
			// render.drawRectangle(transform,1.0,1.0,true);













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