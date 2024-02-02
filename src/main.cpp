#define INCLUDE_EADKPP_3D

#include <cheats.h>
#include "display.h"
#include "eadkpp.h"
#include "palette.h"

#define EADK_APP_NAME "EADK"
#define EADK_API_LEVEL 0

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = EADK_APP_NAME;
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = EADK_API_LEVEL;

int main(int argc, char * argv[]) {
	EADK::Display::clear(Black);

	// camera
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 4.0f);
	glm::vec3 camRot = glm::vec3(0.0f, 0.0f, 0.0f);
	EADK::Graphics::Camera camera(90.0f, 4 / 3, 0.1f, 100.f);
	camera.setPosition(camPos);
	camera.setRotation(camRot);

	// points
	std::vector<glm::vec3> points = {
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f)
	};

	// indeces
	std::vector<glm::uvec3> indeces = {
		glm::uvec3(0, 1, 2),
		glm::uvec3(2, 3, 0),
		glm::uvec3(4, 5, 6),
		glm::uvec3(6, 7, 4),
		glm::uvec3(0, 4, 7),
		glm::uvec3(7, 3, 0),
		glm::uvec3(1, 5, 6),
		glm::uvec3(6, 2, 1),
		glm::uvec3(0, 1, 5),
		glm::uvec3(5, 4, 0),
		glm::uvec3(3, 2, 6),
		glm::uvec3(6, 7, 3)
	};

	float time = 0.0f;
	while (true) {
		EADK::Display::clear(Black);
		time += 0.01f;

		EADK::Display::drawString(10, 10, 3, "HALLO", White, Black, 1, 2, false);

		EADK::Keyboard::State kbd = EADK::Keyboard::scan();
		if (kbd.keyDown(EADK::Keyboard::Key::Right)) {
			camRot.x += 0.1f;
			camera.setRotation(camRot);
		}
		if (kbd.keyDown(EADK::Keyboard::Key::Left)) {
			camRot.x -= 0.1f;
			camera.setRotation(camRot);
		}
		if (kbd.keyDown(EADK::Keyboard::Key::Down)) {
			camRot.y += 0.1f;
			camera.setRotation(camRot);
		}
		if (kbd.keyDown(EADK::Keyboard::Key::Up)) {
			camRot.y -= 0.1f;
			camera.setRotation(camRot);
		}

		// moving
		if (kbd.keyDown(EADK::Keyboard::Key::Four)) {
			camPos.x -= 0.1f;
			camera.setPosition(camPos);
		}
		if (kbd.keyDown(EADK::Keyboard::Key::Six)) {
			camPos.x += 0.1f;
			camera.setPosition(camPos);
		}
		if (kbd.keyDown(EADK::Keyboard::Key::Two)) {
			camPos.y -= 0.1f;
			camera.setPosition(camPos);
		}
		if (kbd.keyDown(EADK::Keyboard::Key::Eight)) {
			camPos.y += 0.1f;
			camera.setPosition(camPos);
		}

		camera.render(points, indeces, White);
		
		EADK::Timing::msleep(10);
	}
	
	return 0;
}