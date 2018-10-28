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

onion_connection_status api_system(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status api_system_sleep(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status api_system_4k2k(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}

onion_connection_status api_system_led(void *unused, onion_request *req, onion_response *res)
{
	API_UNIMPLEMENTED
}
