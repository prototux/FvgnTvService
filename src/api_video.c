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

onion_connection_status  api_video_dynamic_contrast(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_film_mode(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_mute(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_mute_color(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_backlight(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_black_stretch(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_brightness(void *unused, onion_request *req, onion_response *res)
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage POST case: change the brightness
	if ((flags & OR_METHODS) == OR_POST)
	{
		const onion_block *dreq = onion_request_get_data(req);
		onion_dict *jreq = NULL;
		if (dreq)
			jreq = onion_dict_from_json(onion_block_data(dreq));
		if (jreq)
		{
			int brightness = atoi(onion_dict_get(jreq, "value"));
			if (brightness)
				printf("Brightness = %d\n", brightness);
			platform_video_set_brightness(brightness);
			onion_dict *jres = onion_dict_new();
			onion_dict_add(jres, "test", "truc", 0);
			onion_block *jresb = onion_dict_to_json(jres);
			onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
			onion_block_free(jresb);
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

	// Manage GET case: get brightness
	else if ((flags & OR_METHODS) == OR_GET)
	{
		char brightness_str[4];
		snprintf(brightness_str, 4, "%d", platform_video_brightness);
		onion_dict *jres = onion_dict_new();
		onion_dict_add(jres, "value", &brightness_str, 0);
		onion_block *jresb = onion_dict_to_json(jres);
		onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
		onion_block_free(jresb);
		onion_dict_free(jres);
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

onion_connection_status  api_video_contrast(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_flesh_tone(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_game_mode(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_gamma(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_hue(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_noise_reduction(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_saturation(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_sharpness(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_white_balance(void *unused, onion_request *req, onion_response *res)
{
    API_UNIMPLEMENTED
}

