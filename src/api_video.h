#ifndef __API_VIDEO_H__
#define __API_VIDEO_H__

#include <onion/onion.h>
#include <onion/request.h>
#include <onion/response.h>

onion_connection_status  api_video_dynamic_contrast(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_film_mode(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_mute(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_mute_color(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_backlight(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_black_stretch(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_brightness(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_contrast(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_flesh_tone(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_game_mode(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_gamma(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_hue(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_noise_reduction(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_saturation(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_sharpness(void *unused, onion_request *req, onion_response *res);

#endif /* __API_VIDEO_H__ */
