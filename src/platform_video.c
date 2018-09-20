#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <fpp/fpp.h>

#include "platform.h"

uint8_t platform_video_brightness = 0;
uint8_t platform_video_contrast = 0;
uint8_t platform_video_saturation = 0;
uint8_t platform_video_hue = 0;
uint8_t platform_video_sharpness = 0;

// Set brightness
int platform_video_set_brightness(uint8_t value)
{
	// Hardcoded until it's moved to a config file
	const uint8_t min = 35;
	const uint8_t mid = 85;
	const uint8_t max = 190;

	// Brightness value should be between 0 and 100
	if (value > 100)
	{
		printf("ERROR: Brightness should be between 1 and 100, got %d\n", value);
		return 0;
	}

	struct fpp_video_adj adj = {.value=value, .min=min, .low=0, .mid=mid, .high=0, .max=max};
	platform_video_brightness = value;
	fpp_video_set_brightness(1, adj);
	return 1;
}

// Set contrast
int platform_video_set_contrast(uint8_t value)
{
	// Hardcoded until it's moved to a config file
	const uint8_t min = 35;
	const uint8_t mid = 85;
	const uint8_t max = 190;

	// Contrast value should be between 0 and 100
	if (value > 100)
	{
		printf("ERROR: Contrast should be between 1 and 100, got %d\n", value);
		return 0;
	}

	struct fpp_video_adj adj = {.value=value, .min=min, .low=0, .mid=mid, .high=0, .max=max};
	platform_video_contrast = value;
	fpp_video_set_brightness(1, adj);
	return 1;
}

// Set saturation
int platform_video_set_saturation(uint8_t value)
{
	// Hardcoded until it's moved to a config file
	const uint8_t min = 35;
	const uint8_t mid = 85;
	const uint8_t max = 190;

	// Saturation value should be between 0 and 100
	if (value > 100)
	{
		printf("ERROR: Saturation should be between 1 and 100, got %d\n", value);
		return 0;
	}

	struct fpp_video_adj adj = {.value=value, .min=min, .low=0, .mid=mid, .high=0, .max=max};
	platform_video_saturation = value;
	fpp_video_set_saturation(1, adj);
	return 1;
}

// Set hue
int platform_video_set_hue(uint8_t value)
{
	// Hardcoded until it's moved to a config file
	const uint8_t min = 35;
	const uint8_t mid = 85;
	const uint8_t max = 190;

	// Hue value should be between 0 and 100
	if (value > 100)
	{
		printf("ERROR: Hue should be between 1 and 100, got %d\n", value);
		return 0;
	}

	struct fpp_video_adj adj = {.value=value, .min=min, .low=0, .mid=mid, .high=0, .max=max};
	platform_video_hue = value;
	fpp_video_set_hue(1, adj);
	return 1;
}

// Set sharpness
int platform_video_set_sharpness(uint8_t value)
{
	// Hardcoded until it's moved to a config file
	const uint8_t min = 35;
	const uint8_t mid = 85;
	const uint8_t max = 190;

	// Sharpness value should be between 0 and 100
	if (value > 100)
	{
		printf("ERROR: Sharpness should be between 1 and 100, got %d\n", value);
		return 0;
	}

	struct fpp_video_adj adj = {.value=value, .min=min, .low=0, .mid=mid, .high=0, .max=max};
	platform_video_sharpness = value;
	fpp_video_set_sharpness(1, adj);
	return 1;
}

// Set mute color
int platform_video_set_mute_color(uint8_t red, uint8_t green, uint8_t blue)
{
	fpp_video_set_mute_color(red, green, blue);
	return 1;
}

// (un)mute video
int platform_video_mute(uint8_t muted)
{
	fpp_video_mute(muted);
	return 1;
}

// (un)freeze video
int platform_video_freeze(uint8_t frozen)
{
	fpp_video_freeze(frozen);
}
