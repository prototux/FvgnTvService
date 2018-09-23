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

onion_connection_status  api_power(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_power_panel(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_power_led(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_power_methods(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status  api_power_sleep(void *unused, onion_request *req, onion_response *res)
{
	return api_process_bool(req, res, &platform_power_current_fakeoff, &platform_power_fakeoff);
}
