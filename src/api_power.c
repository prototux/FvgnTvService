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
    const onion_block *dreq = onion_request_get_data(req);
    onion_dict *jreq = NULL;
    if (dreq)
        jreq = onion_dict_from_json(onion_block_data(dreq));
    if (jreq)
    {
        //if (s_strcmp(onion_dict_get(jreq, "state"), "on"))
        //    fpp_video_mute(0);
        //if (s_strcmp(onion_dict_get(jreq, "state"), "off"))
        //    fpp_video_mute(1);
        onion_dict *jres = onion_dict_new();
        onion_dict_add(jres, "test", "truc", 0);
        onion_block *jresb = onion_dict_to_json(jres);
        onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
        onion_block_free(jresb);
        onion_dict_free(jres);
        onion_dict_free(jreq);

        return OCS_PROCESSED;
    }
    else
    {
        onion_response_write0(res, "TEST");
        return OCS_PROCESSED;
    }
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
	API_UNIMPLEMENTED
}
