#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <fpp/fpp.h>

#include "platform.h"

uint8_t platform_video_brightness = 0;

int platform_video_set_brightness(uint8_t brightness)
{
	// Hardcoded until it's moved to a config file
	const uint8_t min = 35;
	const uint8_t mid = 85;
	const uint8_t max = 190;

	// Brightness value should be between 0 and 100
	if (brightness > 100)
	{
		printf("ERROR: Brightness should be between 1 and 100, got %d\n", brightness);
		return 0;
	}

	struct fpp_video_adj brightness_adj = {.value=brightness, .min=min, .low=0, .mid=mid, .high=0, .max=max};
	platform_video_brightness = brightness;
	fpp_video_set_brightness(1, brightness_adj);
	return 1;
}
