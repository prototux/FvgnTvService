#ifndef __API_AUDIO_H__
#define __API_AUDIO_H__

#include <onion/onion.h>
#include <onion/request.h>
#include <onion/response.h>

onion_connection_status api_audio_mutes(void *unused, onion_request *req, onion_response *res);

onion_connection_status api_audio_headphones(void *unused, onion_request *req, onion_response *res);

onion_connection_status api_audio_speaker(void *unused, onion_request *req, onion_response *res);

onion_connection_status api_audio_volume(void *unused, onion_request *req, onion_response *res);

onion_connection_status api_audio_mic(void *unused, onion_request *req, onion_response *res);

#endif /* __API_AUDIO_H__ */
