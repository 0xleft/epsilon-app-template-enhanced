#define INCLUDE_EADKPP_3D

#include <cheats.h>
#include "display.h"
#include "eadkpp.h"
#include "palette.h"
#include "windows.h"

#define EADK_APP_NAME "EADK"
#define EADK_API_LEVEL 0

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = EADK_APP_NAME;
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = EADK_API_LEVEL;

int main(int argc, char * argv[]) {
	EADK::Display::clear(Black);

	example::windows::Window window;
	window.runWindow<example::windows::WindowType::GAME>();

	return 0;
}