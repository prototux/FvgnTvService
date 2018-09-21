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

enum mpeg_noise_reduction {mpeg_nr_off, mpeg_nr_low, mpeg_nr_mid, mpeg_nr_high, mpeg_nr_num };
enum color_param  {color_normal, color_enhance_wide, color_xvycc, color_bypass = 255, color_max };

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

// Set backlight (non-dynamic)
int platform_video_set_backlight(uint8_t value)
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
	fpp_video_set_background_light(adj);
	return 1;
}

// Set noise reduction (TODO: more testing)
int platform_video_set_noise_reduction(uint8_t value)
{
	fpp_video_set_noise_reduction(value);
}

// Set black stretch (TODO: more testing)
int platform_video_set_black_stretch(uint8_t value)
{
	fpp_video_set_black_stretch(value);
}

// Set gamma (TODO: more testing)
int platform_video_set_gamma(uint8_t value)
{
	fpp_video_set_gamma(value);
}

// Enable film mode (TODO: more testing)
int platform_video_enable_film_mode(uint8_t enabled)
{
	fpp_video_enable_film_mode(enabled);
}

// Enable dynamic contrast (TODO: more testing)
int platform_video_enable_dynamic_contrast(uint8_t enabled)
{
	fpp_video_enable_dynamic_contrast(enabled);
}

// Set MPEG noise reduction (TODO: more testing)
int platform_video_set_mpeg_noise_reduction(enum mpeg_noise_reduction level)
{
	fpp_video_set_mpeg_nr(level);
}

// Enable flesh tone (TODO: more testing)
int platform_video_enable_flesh_tone(uint8_t enabled)
{
	fpp_video_set_flesh_tone(enabled);
}

// Enable game mode (TODO: more testing)
int platform_video_enable_game_mode(uint8_t enabled)
{
	fpp_video_set_game_mode(enabled);
}

// Set color mode (TODO: more testing)
int platform_video_set_color_param(enum color_param param)
{
	fpp_video_set_color_param(param);
}

// Set white balance/RGB params (TODO: more testing)
int platform_video_set_white_balance(uint16_t r_gain, uint16_t r_offset, uint16_t g_gain, uint16_t g_offset, uint16_t b_gain, uint16_t b_offset)
{
	struct fpp_factory_wb params = {.r_gain=r_gain, .g_gain=g_gain, .g_gain=g_gain, .r_offset=r_offset, .g_offset=g_offset, .b_offset=b_offset};
	fpp_factory_set_white_balance(params);
}

// TODO: fpp_video_set_pq_algorithm
