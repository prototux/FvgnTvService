#ifndef __API_SYSTEM_H__
#define __API_SYSTEM_H__

#include <onion/onion.h>
#include <onion/request.h>
#include <onion/response.h>

onion_connection_status api_system(void *unused, onion_request *req, onion_response *res);

onion_connection_status api_system_sleep(void *unused, onion_request *req, onion_response *res);

onion_connection_status api_system_4k2k(void *unused, onion_request *req, onion_response *res);

onion_connection_status api_system_led(void *unused, onion_request *req, onion_response *res);

#endif /* __API_SYSTEM_H__ */
