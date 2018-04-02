#ifndef __API_ZOOM_H__
#define __API_ZOOM_H__

#include <onion/onion.h>
#include <onion/request.h>
#include <onion/response.h>

onion_connection_status  api_zoom_crop_window(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_zoom_display_window(void *unused, onion_request *req, onion_response *res);

#endif /* __API_ZOOM_H__ */
