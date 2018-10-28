#ifndef __API_VIDEO_H__
#define __API_VIDEO_H__

#include <onion/onion.h>
#include <onion/request.h>
#include <onion/response.h>

onion_connection_status  api_video(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_video_mute(void *unused, onion_request *req, onion_response *res);

#endif /* __API_VIDEO_H__ */
