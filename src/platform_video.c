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
uint8_t platform_video_backlight = 0;
uint8_t platform_video_gamma = 0;
uint8_t platform_video_muted = 0;
uint8_t platform_video_mute_red = 0;
uint8_t platform_video_mute_green = 0;
uint8_t platform_video_mute_blue = 0;
uint8_t platform_video_dynamic_contrast = 0;
uint8_t platform_video_current_film_mode = 0;
uint8_t platform_video_current_game_mode = 0;
uint8_t platform_video_current_flesh_tone = 0;

// Set brightness
uint8_t platform_video_set_brightness(uint8_t value)
{
	// Hardcoded until it's moved to a config file
	const uint8_t min = 35;
	const uint8_t mid = 85;
	const uint8_t max = 190;

	// Brightness value should be between 0 and 100
	if (value > 100)
	{
		printf("ERROR: Brightness should be between 1 and 100, got %d\n", value);
		return E_OUTOFBOUNDS;
	}

	// Create the video_adj struct
	struct fpp_video_adj adj = {.value=value, .min=min, .low=0, .mid=mid, .high=0, .max=max};
	fpp_video_set_brightness(1, adj);
	platform_video_brightness = value;
	return 0;
}

// Set contrast
uint8_t platform_video_set_contrast(uint8_t value)
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
uint8_t platform_video_set_saturation(uint8_t value)
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
uint8_t platform_video_set_hue(uint8_t value)
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
uint8_t platform_video_set_sharpness(uint8_t value)
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
uint8_t platform_video_set_mute_color(uint8_t red, uint8_t green, uint8_t blue)
{
	fpp_video_set_mute_color(red, green, blue);
	platform_video_mute_red = red;
	platform_video_mute_green = green;
	platform_video_mute_blue = blue;
	return 1;
}

// (un)mute video
uint8_t platform_video_mute(uint8_t muted)
{
	fpp_video_mute(muted);
	platform_video_muted = muted;
	return 0;
}

// (un)freeze video
uint8_t platform_video_freeze(uint8_t frozen)
{
	fpp_video_freeze(frozen);
	return 0;
}

// Set backlight (non-dynamic)
uint8_t platform_video_set_backlight(uint8_t value)
{
	// Hardcoded until it's moved to a config file
	const uint8_t min = 35;
	const uint8_t mid = 85;
	const uint8_t max = 190;

	// Backlight value should be between 0 and 100
	if (value > 100)
	{
		printf("ERROR: Backlight should be between 1 and 100, got %d\n", value);
		return 0;
	}

	struct fpp_video_adj adj = {.value=value, .min=min, .low=0, .mid=mid, .high=0, .max=max};
	fpp_video_set_background_light(adj);
	platform_video_backlight = value;
	return 1;
}

// Set noise reduction (TODO: more testing)
uint8_t platform_video_set_noise_reduction(uint8_t value)
{
	fpp_video_set_noise_reduction(value);
	return 0;
}

// Set black stretch (TODO: more testing)
// Should (in theory) make the dark areas look darker
uint8_t platform_video_set_black_stretch(uint8_t value)
{
	fpp_video_set_black_stretch(value);
	return 0;
}

// Set gamma (TODO: more testing)
uint8_t platform_video_set_gamma(uint8_t value)
{
	fpp_video_set_gamma(value);
	return 0;
}

// Enable film mode (TODO: more testing)
// Apparently, it's when you have mpeg2/480p input (such as DVDs)
uint8_t platform_video_enable_film_mode(uint8_t enabled)
{
	fpp_video_enable_film_mode(enabled);
	return 0;
}

// Enable dynamic contrast (TODO: more testing)
// Should adapt the contrast automatically but... not so good
uint8_t platform_video_enable_dynamic_contrast(uint8_t enabled)
{
	fpp_video_enable_dynamic_contrast(enabled);
	return 0;
}

// Set MPEG noise reduction (TODO: more testing)
// Should reduce the MPEG compression noise
uint8_t platform_video_set_mpeg_noise_reduction(enum fpp_mpeg_noise_reduction level)
{
	fpp_video_set_mpeg_nr(level);
	return 0;
}

// Enable flesh tone (TODO: more testing)
// Apparently, it "enhance" the flesh tones, making them more red...
uint8_t platform_video_enable_flesh_tone(uint8_t enabled)
{
	// Apparently fpp doesn't like anything other than 0 or 1
	if (enabled)
		enabled = 1;

	fpp_video_set_flesh_tone(enabled);
	return 0;
}

// Enable game mode (TODO: more testing)
// Apparently, it's for reducing input lag at the expense of quality
uint8_t platform_video_enable_game_mode(uint8_t enabled)
{
	fpp_video_set_game_mode(enabled);
	return 0;
}

// Set color mode (TODO: more testing)
uint8_t platform_video_set_color_param(enum fpp_color_param param)
{
	fpp_video_set_color_param(param);
	return 0;
}

void platform_get_video_size(uint8_t linein, uint16_t *width, uint16_t *height)
{
    fpp_signal_get_video_size(linein, 0, width, height);
}

void platform_get_framerate(uint8_t *framerate)
{
    fpp_signal_get_disp_framerate(framerate);
}
// Set white balance/RGB params (TODO: more testing)
// Currently segfaults
uint8_t platform_video_set_white_balance(uint16_t r_gain, uint16_t r_offset, uint16_t g_gain, uint16_t g_offset, uint16_t b_gain, uint16_t b_offset)
{
	// I have no idea why they did this in uint16s if they check for uint8 boundaries after but well... that's what fpi_video_set_rgb do
	if (r_gain > 0xff || r_offset > 0xff || g_gain > 0xff || g_offset > 0xff || b_gain > 0xff || b_offset > 0xff)
	{
		printf("ERROR: A parameter is out of bound (max is 0xff)\n");
		return E_OUTOFBOUNDS;
	}

	// Create the structure, it's not in the same order as the parameters!
	struct fpp_factory_wb params = {
		.r_gain=r_gain,
		.g_gain=g_gain,
		.b_gain=b_gain,
		.r_offset=r_offset,
		.g_offset=g_offset,
		.b_offset=b_offset
	};

	// Call libfpp
	if (!fpp_factory_set_white_balance(&params))
	{
		printf("ERROR: fpp_factory_set_white_balance returned an error\n");
		return E_FPPRET;
	}
	return 0;
}

uint8_t platform_video_get_blackfield_status()
{
	uint8_t status;
	fpp_video_get_black_field_status(&status);
	return status;
}
