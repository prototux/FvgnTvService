#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include <onion/onion.h>
#include <onion/dict.h>
#include <onion/block.h>
#include <onion/request.h>
#include <onion/response.h>
#include <onion/url.h>
#include <onion/low.h>

#include "tools.h"
#include "api.h"
#include "platform.h"

void api_dict_add_uint8(onion_dict *dict, char *key, uint8_t value)
{
	char value_str[4];
	snprintf(&value_str, 4, "%d", value);
	onion_dict_add(dict, key, &value_str, OD_DUP_VALUE);
}

void api_dict_add_uint16(onion_dict *dict, char *key, uint16_t value)
{
	char value_str[6];
	snprintf(&value_str, 6, "%d", value);
	onion_dict_add(dict, key, &value_str, OD_DUP_VALUE);
}

void api_dict_add_uint32(onion_dict *dict, char *key, uint32_t value)
{
	char value_str[8];
	snprintf(&value_str, 8, "%d", value);
	onion_dict_add(dict, key, &value_str, OD_DUP_VALUE);
}

onion_dict *api_video_get_current_mute_status(void)
{
	onion_dict *status = onion_dict_new();
	onion_dict_add(status, "mute", (platform_video_muted)?"true":"false", 0);

	// Create color dict
	onion_dict *color = onion_dict_new();
	api_dict_add_uint8(color, "red", platform_video_mute_red);
	api_dict_add_uint8(color, "green", platform_video_mute_green);
	api_dict_add_uint8(color, "blue", platform_video_mute_blue);

	// Add color to status and return
	onion_dict_add(status, "color", color, OD_DICT);
	return status;
}

onion_dict *api_video_get_current_status(void)
{
	onion_dict *status = onion_dict_new();

	// brightness
	api_dict_add_uint8(status, "brightness", platform_video_brightness);

	// contrast
	api_dict_add_uint8(status, "contrast", platform_video_contrast);

	// saturation
	api_dict_add_uint8(status, "saturation", platform_video_saturation);

	// hue
	api_dict_add_uint8(status, "hue", platform_video_hue);

	// sharpness
	api_dict_add_uint8(status, "sharpness", platform_video_sharpness);

	// backlight
	api_dict_add_uint8(status, "backlight", platform_video_backlight);

	// gamma
	api_dict_add_uint8(status, "gamma", platform_video_gamma);

	// dynamic_contrast
	onion_dict_add(status, "dynamic_contrast", (platform_video_dynamic_contrast)?"true":"false", 0);

	// film_mode
	onion_dict_add(status, "film_mode", (platform_video_current_film_mode)?"true":"false", 0);

	// game mode
	onion_dict_add(status, "game_mode", (platform_video_current_game_mode)?"true":"false", 0);

	// flesh_tone
	onion_dict_add(status, "flesh_tone", (platform_video_current_flesh_tone)?"true":"false", 0);

	// mirrored
	onion_dict_add(status, "mirrored", (platform_panel_current_video_mirror)?"true":"false", 0);

	// black_stretch
	// TODO

	// noise_reduction
	// TODO

	// mpeg_nr
	// TODO

	// white_balance
	onion_dict *wb = onion_dict_new();
	api_dict_add_uint16(wb, "red_gain", platform_video_white_balance[0]);
	api_dict_add_uint16(wb, "red_offset", platform_video_white_balance[1]);
	api_dict_add_uint16(wb, "green_gain", platform_video_white_balance[2]);
	api_dict_add_uint16(wb, "green_offset", platform_video_white_balance[3]);
	api_dict_add_uint16(wb, "blue_gain", platform_video_white_balance[4]);
	api_dict_add_uint16(wb, "blue_offset", platform_video_white_balance[5]);
	onion_dict_add(status, "white_balance", wb, OD_DICT);

	// black_field
	api_dict_add_uint8(status, "black_field", platform_video_get_blackfield_status());

	// average_luma
	api_dict_add_uint8(status, "average_luma", platform_panel_get_average_luma());

	// luma_distribution
	//api_dict_add_uint8_t(status, "luma_distribution", "NOT_IMPLEMENTED", 0);

	// crop
	onion_dict *crop = onion_dict_new();
	api_dict_add_uint32(crop, "start_x", platform_zoom_current_crop_start_x);
	api_dict_add_uint32(crop, "start_y", platform_zoom_current_crop_start_y);
	api_dict_add_uint32(crop, "width", platform_zoom_current_crop_width);
	api_dict_add_uint32(crop, "height", platform_zoom_current_crop_height);
	onion_dict_add(status, "crop", crop, OD_DICT);

	// window
	onion_dict *window = onion_dict_new();
	api_dict_add_uint32(window, "pos_x", platform_zoom_current_window_pos_x);
	api_dict_add_uint32(window, "pos_y", platform_zoom_current_window_pos_y);
	api_dict_add_uint32(window, "width", platform_zoom_current_window_width);
	api_dict_add_uint32(window, "height", platform_zoom_current_window_height);
	onion_dict_add(status, "window", window, OD_DICT);

	return status;
}


onion_connection_status api_video(void *unused, onion_request *req, onion_response *res)
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage POST case: Change settings
	if ((flags & OR_METHODS) == OR_POST)
	{
		// Try to get POST data and parse json from it
		const onion_block *dreq = onion_request_get_data(req);
		onion_dict *jreq = NULL;
		if (dreq)
			jreq = onion_dict_from_json(onion_block_data(dreq));
		if (jreq)
		{
			// Set brightness
			if (onion_dict_get(jreq, "brightness"))
			{
				uint8_t brightness = atoi(onion_dict_get(jreq, "brightness"));
				platform_video_set_brightness(brightness);
			}

			// Set contrast
			if (onion_dict_get(jreq, "contrast"))
				platform_video_set_contrast(atoi(onion_dict_get(jreq, "contrast")));

			// Set saturation
			if (onion_dict_get(jreq, "saturation"))
				platform_video_set_saturation(atoi(onion_dict_get(jreq, "saturation")));

			// Set hue
			if (onion_dict_get(jreq, "hue"))
				platform_video_set_hue(atoi(onion_dict_get(jreq, "hue")));

			// Set sharpness
			if (onion_dict_get(jreq, "sharpness"))
				platform_video_set_sharpness(atoi(onion_dict_get(jreq, "sharpness")));

			// Set backlight
			if (onion_dict_get(jreq, "backlight"))
				platform_video_set_sharpness(atoi(onion_dict_get(jreq, "backlight")));

			// Set gamma
			if (onion_dict_get(jreq, "gamma"))
				platform_video_set_gamma(atoi(onion_dict_get(jreq, "gamma")));

			// Set dynamic contrast
			if (onion_dict_get(jreq, "dynamic_contrast"))
				platform_video_enable_dynamic_contrast(!strcmp(onion_dict_get(jreq, "dynamic_contrast"), "true"));

			// Set film mode
			if (onion_dict_get(jreq, "film_mode"))
				platform_video_enable_film_mode(!strcmp(onion_dict_get(jreq, "film_mode"), "true"));

			// Set game mode
			if (onion_dict_get(jreq, "game_mode"))
				platform_video_enable_game_mode(!strcmp(onion_dict_get(jreq, "game_mode"), "true"));

			// Set flesh tone
			if (onion_dict_get(jreq, "flesh_tone"))
				platform_video_enable_flesh_tone(!strcmp(onion_dict_get(jreq, "flesh_tone"), "true"));

			// Set mirrored
			if (onion_dict_get(jreq, "mirrored"))
				platform_panel_set_video_mirror(!strcmp(onion_dict_get(jreq, "mirrored"), "true"));

			// Set black stretch
			if (onion_dict_get(jreq, "black_stretch"))
			{
				if (!strcmp(onion_dict_get(jreq, "black_stretch"), "off"))
					platform_video_set_black_stretch(0);
				else if (!strcmp(onion_dict_get(jreq, "black_stretch"), "dark"))
					platform_video_set_black_stretch(1);
				else if (!strcmp(onion_dict_get(jreq, "black_stretch"), "darker"))
					platform_video_set_black_stretch(2);
				else if (!strcmp(onion_dict_get(jreq, "black_stretch"), "darkest"))
					platform_video_set_black_stretch(3);
			}

			// Set noise reduction
			// off, low, mid, high, auto
			if (onion_dict_get(jreq, "noise_reduction"))
			{
				if (!strcmp(onion_dict_get(jreq, "noise_reduction"), "off"))
					platform_video_set_noise_reduction(0);
				else if (!strcmp(onion_dict_get(jreq, "noise_reduction"), "low"))
					platform_video_set_noise_reduction(1);
				else if (!strcmp(onion_dict_get(jreq, "noise_reduction"), "mid"))
					platform_video_set_noise_reduction(2);
				else if (!strcmp(onion_dict_get(jreq, "noise_reduction"), "high"))
					platform_video_set_noise_reduction(3);
				if (!strcmp(onion_dict_get(jreq, "noise_reduction"), "auto"))
					platform_video_set_noise_reduction(4);
			}

			// Set MPEG noise reduction
			// off, low, mid, high, num
			if (onion_dict_get(jreq, "mpeg_nr"))
			{
				if (!strcmp(onion_dict_get(jreq, "mpeg_nr"), "off"))
					platform_video_set_mpeg_noise_reduction(0);
				else if (!strcmp(onion_dict_get(jreq, "mpeg_nr"), "low"))
					platform_video_set_mpeg_noise_reduction(1);
				else if (!strcmp(onion_dict_get(jreq, "mpeg_nr"), "mid"))
					platform_video_set_mpeg_noise_reduction(2);
				else if (!strcmp(onion_dict_get(jreq, "mpeg_nr"), "high"))
					platform_video_set_mpeg_noise_reduction(3);
				else if (!strcmp(onion_dict_get(jreq, "mpeg_nr"), "num"))
					platform_video_set_mpeg_noise_reduction(4);
			}

			// Set white balance
			onion_dict *wb = onion_dict_get_dict(jreq, "white_balance");
			if (wb)
			{
				uint16_t r_gain = (onion_dict_get(wb, "red_gain"))? atoi(onion_dict_get(wb, "red_gain")) : 0;
				uint16_t r_offset = (onion_dict_get(wb, "red_offset"))? atoi(onion_dict_get(wb, "red_offset")) : 0;
				uint16_t g_gain = (onion_dict_get(wb, "green_gain"))? atoi(onion_dict_get(wb, "green_gain")) : 0;
				uint16_t g_offset = (onion_dict_get(wb, "green_offset"))? atoi(onion_dict_get(wb, "green_offset")) : 0;
				uint16_t b_gain = (onion_dict_get(wb, "blue_gain"))? atoi(onion_dict_get(wb, "red_gain")) : 0;
				uint16_t b_offset = (onion_dict_get(wb, "blue_offset"))? atoi(onion_dict_get(wb, "red_offset")) : 0;
				platform_video_set_white_balance(r_gain, r_offset, g_gain, g_offset, b_gain, b_offset);
			}

			// Set window crop
			onion_dict *crop = onion_dict_get_dict(jreq, "crop");
			if (crop)
			{
				uint32_t start_x = (onion_dict_get(crop, "start_x"))? atoi(onion_dict_get(crop, "start_x")) : 0;
				uint32_t start_y = (onion_dict_get(crop, "start_y"))? atoi(onion_dict_get(crop, "start_y")) : 0;
				uint32_t width = (onion_dict_get(crop, "width"))? atoi(onion_dict_get(crop, "width")) : 0;
				uint32_t height = (onion_dict_get(crop, "height"))? atoi(onion_dict_get(crop, "height")) : 0;
				platform_window_crop(platform_input_current_linein, start_x, start_y, width, height);
			}

			// Set window position
			onion_dict *window = onion_dict_get_dict(jreq, "window");
			if (window)
			{
				uint32_t pos_x = (onion_dict_get(window, "pos_x"))? atoi(onion_dict_get(window, "pos_x")) : 0;
				uint32_t pos_y = (onion_dict_get(window, "pos_y"))? atoi(onion_dict_get(window, "pos_y")) : 0;
				uint32_t width = (onion_dict_get(window, "width"))? atoi(onion_dict_get(window, "width")) : 0;
				uint32_t height = (onion_dict_get(window, "height"))? atoi(onion_dict_get(window, "height")) : 0;
				platform_window_pos(platform_input_current_linein, pos_x, pos_y, width, height);
			}

			// Build response dict
			onion_dict *jres = onion_dict_new();
			onion_dict_add(jres, "status", "success", 0);
			onion_dict_merge(jres, api_video_get_current_status());

			// Build json from dict, send it back, and free the json.
			onion_block *jresb = onion_dict_to_json(jres);
			onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
			onion_block_free(jresb);

			// Clean up
			onion_dict_free(jres);
			onion_dict_free(jreq);

			return OCS_PROCESSED;
		}
		else
		{
			onion_response_set_code(res, 400);
			onion_response_write0(res, API_BADREQUEST_JSON);
			return OCS_PROCESSED;
		}
	}

	// Manage GET case: get current status and color
	else if ((flags & OR_METHODS) == OR_GET)
	{
		onion_block *jresb = onion_dict_to_json(api_video_get_current_status());
		onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
		onion_block_free(jresb);
		return OCS_PROCESSED;
	}

	// Return error for other cases
	else
	{
		onion_response_set_code(res, 405);
		onion_response_write0(res, API_BADMETHOD_JSON);
		return OCS_PROCESSED;
	}
}

onion_connection_status api_video_mute(void *unused, onion_request *req, onion_response *res)
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage POST case: mute/unmute and change the color
	if ((flags & OR_METHODS) == OR_POST)
	{
		// Try to get POST data and parse json from it
		const onion_block *dreq = onion_request_get_data(req);
		onion_dict *jreq = NULL;
		if (dreq)
			jreq = onion_dict_from_json(onion_block_data(dreq));
		if (jreq)
		{
			// Get mute
			int mute = !strcmp(onion_dict_get(jreq, "mute"), "true");

			// Get color
			onion_dict *color = onion_dict_get_dict(jreq, "color");
			if (color)
			{
				// Get each color, checking first if it was defined in the JSON, then set the mute color
				uint8_t color_red = (onion_dict_get(color, "red"))? atoi(onion_dict_get(color, "red")) : 0;
				uint8_t color_green = (onion_dict_get(color, "green"))? atoi(onion_dict_get(color, "green")) : 0;
				uint8_t color_blue = (onion_dict_get(color, "blue"))? atoi(onion_dict_get(color, "blue")) : 0;
				printf("Set mute color: (%d, %d, %d)\n", color_red, color_green, color_blue);
				platform_video_set_mute_color(color_red, color_green, color_blue);
			}

			// Mute/unmute the video **after** setting color
			platform_video_mute(mute);

			// Build response dict
			onion_dict *jres = onion_dict_new();
			onion_dict_add(jres, "status", "success", 0);
			onion_dict_merge(jres, api_video_get_current_mute_status());

			// Build json from dict, send it back, and free the json.
			onion_block *jresb = onion_dict_to_json(jres);
			onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
			onion_block_free(jresb);

			// Clean up
			onion_dict_free(jres);
			onion_dict_free(jreq);

			return OCS_PROCESSED;
		}
		else
		{
			onion_response_set_code(res, 400);
			onion_response_write0(res, API_BADREQUEST_JSON);
			return OCS_PROCESSED;
		}
	}

	// Manage GET case: get current status and color
	else if ((flags & OR_METHODS) == OR_GET)
	{
		onion_block *jresb = onion_dict_to_json(api_video_get_current_mute_status());
		onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
		onion_block_free(jresb);
		return OCS_PROCESSED;
	}

	// Return error for other cases
	else
	{
		onion_response_set_code(res, 405);
		onion_response_write0(res, API_BADMETHOD_JSON);
		return OCS_PROCESSED;
	}
}
