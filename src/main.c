#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include <fpp/fpp.h>
#include <onion/onion.h>
#include <onion/dict.h>
#include <onion/block.h>
#include <onion/request.h>
#include <onion/response.h>
#include <onion/url.h>
#include <onion/low.h>
#include <inih/ini.h>

#include "tools.h"
#include "api.h"
#include "platform.h"

int main(int argc, char *argv[])
{
	// Init configuration
	if (!platform_init_config())
	{
		printf("Cannot init config!\n");
		return EXIT_FAILURE;
	}

	// Init FPP
	if (!platform_init_fpp())
	{
		printf("Cannot init FPP!\n");
		return EXIT_FAILURE;
	}

	// Init video & LED
	if (!platform_init_video())
	{
		printf("Cannot init video\n");
		return EXIT_FAILURE;
	}
	platform_power_set_led(0);

	// Libonion init
	onion *o = onion_new(O_ONE_LOOP);
	onion_url *url = onion_root_url(o);

	// Video endpoints
	onion_url_add(url, "^video$", api_video);
	onion_url_add(url, "video/mute", api_video_mute);

	// Input endpoints
	onion_url_add(url, "^input$", api_input);
	onion_url_add(url, "input/plugged", api_input_plugged);

	// System endpoints
	onion_url_add(url, "^$", api_system);
	onion_url_add(url, "^system$", api_system);
	onion_url_add(url, "system/sleep", api_system_sleep);
	onion_url_add(url, "system/4k2k", api_system_4k2k);
	onion_url_add(url, "system/led", api_system_led);

	// Listen
	onion_listen(o);
	return EXIT_SUCCESS;
}
