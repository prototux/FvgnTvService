#ifndef __API_ALL_H__
#define __API_ALL_H__

#include "api_input.h"
#include "api_system.h"
#include "api_video.h"

#define API_BADREQUEST_JSON "{\"error\": 400, \"message\": \"No data\"}"
#define API_BADMETHOD_JSON "{\"error\": 405, \"message\": \"Method not allowed\"}"

onion_connection_status api_process_linear(onion_request *req, onion_response *res, uint8_t *current_value, uint8_t (*set_function)(uint8_t));
onion_connection_status api_process_bool(onion_request *req, onion_response *res, uint8_t *current_value, uint8_t (*set_function)(uint8_t));

#endif /* __API_ALL_H__ */
