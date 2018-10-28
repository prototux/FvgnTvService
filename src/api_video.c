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

onion_dict *api_video_get_current_mute_status(void)
{
	onion_dict *status = onion_dict_new();
	onion_dict_add(status, "mute", (platform_video_muted)?"true":"false", 0);

	// Create color dict
	onion_dict *color = onion_dict_new();
	char red_str[4];
	snprintf(&red_str, 4, "%d", platform_video_mute_red);
	onion_dict_add(color, "red", &red_str, OD_DUP_VALUE);

	char green_str[4];
	snprintf(&green_str, 4, "%d", platform_video_mute_green);
	onion_dict_add(color, "green", &green_str, OD_DUP_VALUE);

	char blue_str[4];
	snprintf(&blue_str, 4, "%d", platform_video_mute_blue);
	onion_dict_add(color, "blue", &blue_str, OD_DUP_VALUE);

	// Add color to status and return
	onion_dict_add(status, "color", color, OD_DICT);
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
			// Get & set brightness
			if (onion_dict_get(jreq, "brightness"))
			{
				uint8_t brightness = atoi(onion_dict_get(jreq, "brightness"));
				platform_video_set_brightness(brightness);
			}

			// Get contrast
			if (onion_dict_get(jreq, "contrast"))
			{
				uint8_t contrast = atoi(onion_dict_get(jreq, "contrast"));
				platform_video_set_contrast(contrast);
			}

			// Get saturation
			if (onion_dict_get(jreq, "saturation"))
			{
				uint8_t saturation = atoi(onion_dict_get(jreq, "saturation"));
				platform_video_set_saturation(saturation);
			}

			// Get hue
			if (onion_dict_get(jreq, "hue"))
			{
				uint8_t hue = atoi(onion_dict_get(jreq, "hue"));
				platform_video_set_hue(hue);
			}

			// Get sharpness
			if (onion_dict_get(jreq, "sharpness"))
			{
				uint8_t sharpness = atoi(onion_dict_get(jreq, "sharpness"));
				platform_video_set_sharpness(sharpness);
			}

			// Get backlight
			if (onion_dict_get(jreq, "backlight"))
			{
				uint8_t backlight = atoi(onion_dict_get(jreq, "backlight"));
				platform_video_set_sharpness(backlight);
			}

			// Get gamma
			if (onion_dict_get(jreq, "gamma"))
			{
				uint8_t gamma = atoi(onion_dict_get(jreq, "gamma"));
				platform_video_set_gamma(gamma);
			}

			// Get dynamic contrast
			if (onion_dict_get(jreq, "dynamic_contrast"))
				platform_video_enable_dynamic_contrast(!strcmp(onion_dict_get(jreq, "dynamic_contrast"), "true"));

			// Get film mode
			if (onion_dict_get(jreq, "film_mode"))
				platform_video_enable_film_mode(!strcmp(onion_dict_get(jreq, "film_mode"), "true"));

			// Get game mode
			if (onion_dict_get(jreq, "game_mode"))
				platform_video_enable_game_mode(!strcmp(onion_dict_get(jreq, "game_mode"), "true"));

			// Get flesh tone
			if (onion_dict_get(jreq, "flesh_tone"))
				platform_video_enable_flesh_tone(!strcmp(onion_dict_get(jreq, "flesh_tone"), "true"));

			// Get mirrored
			if (onion_dict_get(jreq, "mirrored"))
				platform_panel_set_video_mirror(!strcmp(onion_dict_get(jreq, "mirrored"), "true"));

			// Get black stretch

			// Get noise reduction

			// Get MPEG noise reduction

			// Get white balance

			// Get window crop

			// Get window position

			// Build response dict
			onion_dict *jres = onion_dict_new();
			onion_dict_add(jres, "status", "success", 0);

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
