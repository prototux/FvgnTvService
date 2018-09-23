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
	return api_process_bool(req, res, &platform_video_dynamic_contrast, &platform_video_enable_dynamic_contrast);
}

onion_connection_status  api_video_film_mode(void *unused, onion_request *req, onion_response *res)
{
	return api_process_bool(req, res, &platform_video_current_film_mode, &platform_video_enable_film_mode);
}

onion_connection_status  api_video_mute(void *unused, onion_request *req, onion_response *res)
{
	return api_process_bool(req, res, &platform_video_muted, &platform_video_mute);
}

onion_connection_status  api_video_mute_color(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_backlight(void *unused, onion_request *req, onion_response *res)
{
	return api_process_linear(req, res, &platform_video_backlight, &platform_video_set_backlight);
}

onion_connection_status  api_video_black_stretch(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_brightness(void *unused, onion_request *req, onion_response *res)
{
	return api_process_linear(req, res, &platform_video_brightness, &platform_video_set_brightness);
}

onion_connection_status  api_video_contrast(void *unused, onion_request *req, onion_response *res)
{
	return api_process_linear(req, res, &platform_video_contrast, &platform_video_set_contrast);
}

onion_connection_status  api_video_flesh_tone(void *unused, onion_request *req, onion_response *res)
{
	return api_process_bool(req, res, &platform_video_current_flesh_tone, &platform_video_enable_flesh_tone);
}

onion_connection_status  api_video_game_mode(void *unused, onion_request *req, onion_response *res)
{
	return api_process_bool(req, res, &platform_video_current_game_mode, &platform_video_enable_game_mode);
}

onion_connection_status  api_video_gamma(void *unused, onion_request *req, onion_response *res)
{
	return api_process_linear(req, res, &platform_video_gamma, &platform_video_set_gamma);
}

onion_connection_status  api_video_hue(void *unused, onion_request *req, onion_response *res)
{
	return api_process_linear(req, res, &platform_video_hue, &platform_video_set_hue);
}

onion_connection_status  api_video_noise_reduction(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_video_saturation(void *unused, onion_request *req, onion_response *res)
{
	return api_process_linear(req, res, &platform_video_saturation, &platform_video_set_saturation);
}

onion_connection_status  api_video_sharpness(void *unused, onion_request *req, onion_response *res)
{
	return api_process_linear(req, res, &platform_video_sharpness, &platform_video_set_sharpness);
}

onion_connection_status  api_video_white_balance(void *unused, onion_request *req, onion_response *res)
{
    API_UNIMPLEMENTED
}

