#ifndef __API_INPUT_H__
#define __API_INPUT_H__

#include <onion/onion.h>
#include <onion/request.h>
#include <onion/response.h>

onion_connection_status  api_input(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_input_plugged(void *unused, onion_request *req, onion_response *res);

#endif /* __API_INPUT_H__ */
