#ifndef __API_POWER_H__
#define __API_POWER_H__

#include <onion/onion.h>
#include <onion/request.h>
#include <onion/response.h>

onion_connection_status  api_power(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_power_panel(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_power_led(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_power_methods(void *unused, onion_request *req, onion_response *res);

onion_connection_status  api_power_sleep(void *unused, onion_request *req, onion_response *res);

#endif /* __API_POWER_H__ */
