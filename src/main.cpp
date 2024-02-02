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

	float time = 0.0f;
	while (true) {
		EADK::Display::clear(Black);
		time += 0.01f;

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


		glm::vec3 p1 = glm::vec3(-1.0f, -1.0f, -1.0f);
		glm::vec3 p2 = glm::vec3(1.0f, -1.0f, -1.0f);
		glm::vec3 p3 = glm::vec3(1.0f, 1.0f, -1.0f);
		glm::vec3 p4 = glm::vec3(-1.0f, 1.0f, -1.0f);
		glm::vec3 p5 = glm::vec3(-1.0f, -1.0f, 1.0f);
		glm::vec3 p6 = glm::vec3(1.0f, -1.0f, 1.0f);
		glm::vec3 p7 = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 p8 = glm::vec3(-1.0f, 1.0f, 1.0f);

		EADK::Display::drawLine(camera.project(p1), camera.project(p2), White);
		EADK::Display::drawLine(camera.project(p2), camera.project(p3), White);
		EADK::Display::drawLine(camera.project(p3), camera.project(p4), White);
		EADK::Display::drawLine(camera.project(p4), camera.project(p1), White);
		
		EADK::Display::drawLine(camera.project(p5), camera.project(p6), White);
		EADK::Display::drawLine(camera.project(p6), camera.project(p7), White);
		EADK::Display::drawLine(camera.project(p7), camera.project(p8), White);
		EADK::Display::drawLine(camera.project(p8), camera.project(p5), White);

		EADK::Display::drawLine(camera.project(p1), camera.project(p5), White);
		EADK::Display::drawLine(camera.project(p2), camera.project(p6), White);
		EADK::Display::drawLine(camera.project(p3), camera.project(p7), White);
		EADK::Display::drawLine(camera.project(p4), camera.project(p8), White);

		EADK::Timing::msleep(10);
	}
	
	return 0;
}