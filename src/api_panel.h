#ifndef __API_PANEL_H__
#define __API_PANEL_H__

#include <onion/onion.h>
#include <onion/request.h>
#include <onion/response.h>

onion_connection_status  api_panel_video_mirror(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_panel_osd_mirror(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_panel_bit_mode(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_panel_polarity(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_panel_swap_port(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_panel_ti_mode(void *unused, onion_request *req, onion_response *res);

#endif /* __API_PANEL_H__ */
