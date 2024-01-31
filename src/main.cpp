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
	EADK::Display::clear(White);

	EADK::Graphics::Vector3 v1(10, 10, 10);
	EADK::Graphics::Vector3 v2(20, 20, 20);
	EADK::Graphics::Vector3 v3 = v1 + v2;

	// cam
	EADK::Graphics::Vector3 camPos(0, 0, 0);
	EADK::Graphics::Vector3 camRot(0, 0, 0);
	EADK::Graphics::Camera camera(camPos, camRot, 80, 16/9, 0.1, 1000);

	// draw vertices
	EADK::Point p1 = camera.project(v1);
	EADK::Point p2 = camera.project(v2);
	EADK::Point p3 = camera.project(v3);

	EADK::Display::drawLine(p1, p2, Black);
	EADK::Display::drawLine(p2, p3, Black);
	EADK::Display::drawLine(p3, p1, Black);

	EADK::Timing::msleep(1000);
}