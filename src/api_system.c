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

onion_connection_status api_system(void *unused, onion_request *req, onion_response *res)
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage GET case: get system infos
	if ((flags & OR_METHODS) == OR_GET)
	{
		onion_dict *jres = onion_dict_new();

		// health
		onion_dict_add(jres, "health", "ok", 0);

		// version
		// TODO
		onion_dict_add(jres, "version", "alpha", 0);

		// model_name
		// TODO
		onion_dict_add(jres, "model_name", "unknown", 0);

		// panel_size
		uint16_t width = 1920, height = 1080;
		platform_panel_get_resolution(&width, &height);
		onion_dict *resolution = onion_dict_new();
		api_dict_add_uint16(resolution, "width", width);
		api_dict_add_uint16(resolution, "height", height);
		onion_dict_add(jres, "panel_size", resolution, OD_DICT);

		// inputs
		// TODO

		onion_block *jresb = onion_dict_to_json(jres);
		onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
		onion_dict_free(jres);
		onion_block_free(jresb);
		return OCS_PROCESSED;
	}

	// Return error for other cases
	else
	{
		onion_response_set_code(res, 405);
		onion_response_write0(res, API_BADMETHOD_JSON);
		return OCS_PROCESSED;
	}
}

onion_connection_status api_system_sleep(void *unused, onion_request *req, onion_response *res)
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage POST case: Set LED
	if ((flags & OR_METHODS) == OR_POST)
	{
		// Try to get POST data and parse json from it
		const onion_block *dreq = onion_request_get_data(req);
		onion_dict *jreq = NULL;
		if (dreq)
			jreq = onion_dict_from_json(onion_block_data(dreq));
		if (jreq)
		{
			uint8_t fulloff = 0;
			uint8_t sleep = 0;

			if (onion_dict_get(jreq, "sleep"))
				sleep = !strcmp(onion_dict_get(jreq, "sleep"), "true");
			if (onion_dict_get(jreq, "mode"))
				fulloff = !strcmp(onion_dict_get(jreq, "mode"), "poweroff");

			// This will not return.. machine is going OFF!
			if (fulloff && sleep)
				platform_power_poweroff();

			// FakeOFF mode
			platform_power_fakeoff(sleep);

			// Build response dict
			onion_dict *jres = onion_dict_new();
			onion_dict_add(jres, "status", "success", 0);
			onion_dict_add(jres, "power", (platform_power_current_fakeoff)? "off":"on", 0);
			onion_dict_add(jres, "mode", "fakeoff", 0);

			// Build json from dict, send it back, and free the json.
			onion_block *jresb = onion_dict_to_json(jres);
			onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
			onion_block_free(jresb);

			// Clean up
			onion_dict_free(jres);
			onion_dict_free(jreq);

			return OCS_PROCESSED;
		}
		else
		{
			onion_response_set_code(res, 400);
			onion_response_write0(res, API_BADREQUEST_JSON);
			return OCS_PROCESSED;
		}
	}

	// Manage GET case: get current status and color
	else if ((flags & OR_METHODS) == OR_GET)
	{
		onion_dict *jres = onion_dict_new();
		onion_dict_add(jres, "mode", "fakeoff", 0);
		onion_dict_add(jres, "power", (platform_power_current_fakeoff)? "off":"on", 0);
		onion_block *jresb = onion_dict_to_json(jres);
		onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
		onion_dict_free(jres);
		onion_block_free(jresb);
		return OCS_PROCESSED;
	}

	// Return error for other cases
	else
	{
		onion_response_set_code(res, 405);
		onion_response_write0(res, API_BADMETHOD_JSON);
		return OCS_PROCESSED;
	}
}

onion_connection_status api_system_4k2k(void *unused, onion_request *req, onion_response *res)
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage POST case: Set LED
	if ((flags & OR_METHODS) == OR_POST)
	{
		// Try to get POST data and parse json from it
		const onion_block *dreq = onion_request_get_data(req);
		onion_dict *jreq = NULL;
		if (dreq)
			jreq = onion_dict_from_json(onion_block_data(dreq));
		if (jreq)
		{
			if (!strcmp(onion_dict_get(jreq, "mode"), "4k2k"))
				platform_system_enter_4k2k_mode(MODE_4K2K);
			else if (platform_system_is_4k2k_mode() != 1)
				platform_system_exit_4k2k_mode(MODE_4K2K);

			// Build response dict
			onion_dict *jres = onion_dict_new();
			onion_dict_add(jres, "status", "success", 0);
			onion_dict_add(jres, "mode", (platform_system_is_4k2k_mode() == 1)? "normal":"4k2k", 0);

			// Build json from dict, send it back, and free the json.
			onion_block *jresb = onion_dict_to_json(jres);
			onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
			onion_block_free(jresb);

			// Clean up
			onion_dict_free(jres);
			onion_dict_free(jreq);

			return OCS_PROCESSED;
		}
		else
		{
			onion_response_set_code(res, 400);
			onion_response_write0(res, API_BADREQUEST_JSON);
			return OCS_PROCESSED;
		}
	}

	// Manage GET case: get current status and color
	else if ((flags & OR_METHODS) == OR_GET)
	{
		onion_dict *jres = onion_dict_new();
		onion_dict_add(jres, "mode", (platform_system_is_4k2k_mode() == 1)? "normal":"4k2k", 0);
		onion_block *jresb = onion_dict_to_json(jres);
		onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
		onion_dict_free(jres);
		onion_block_free(jresb);
		return OCS_PROCESSED;
	}

	// Return error for other cases
	else
	{
		onion_response_set_code(res, 405);
		onion_response_write0(res, API_BADMETHOD_JSON);
		return OCS_PROCESSED;
	}
}

onion_connection_status api_system_led(void *unused, onion_request *req, onion_response *res)
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage POST case: Set LED
	if ((flags & OR_METHODS) == OR_POST)
	{
		// Try to get POST data and parse json from it
		const onion_block *dreq = onion_request_get_data(req);
		onion_dict *jreq = NULL;
		if (dreq)
			jreq = onion_dict_from_json(onion_block_data(dreq));
		if (jreq)
		{
			uint8_t mode = 0;

			// LED On or LED breathing?
			if (!strcmp(onion_dict_get(jreq, "mode"), "on"))
				mode = 1;
			else if (!strcmp(onion_dict_get(jreq, "mode"), "breathing"))
				mode = 2;

			platform_power_set_led(mode);

			// Build response dict
			onion_dict *jres = onion_dict_new();
			onion_dict_add(jres, "status", "success", 0);
			onion_dict_add(jres, "mode", (platform_power_get_led())? "on":"off", 0);

			// Build json from dict, send it back, and free the json.
			onion_block *jresb = onion_dict_to_json(jres);
			onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
			onion_block_free(jresb);

			// Clean up
			onion_dict_free(jres);
			onion_dict_free(jreq);

			return OCS_PROCESSED;
		}
		else
		{
			onion_response_set_code(res, 400);
			onion_response_write0(res, API_BADREQUEST_JSON);
			return OCS_PROCESSED;
		}
	}

	// Manage GET case: get current status and color
	else if ((flags & OR_METHODS) == OR_GET)
	{
		onion_dict *jres = onion_dict_new();
		onion_dict_add(jres, "mode", (platform_power_get_led())? "on":"off", 0);
		onion_block *jresb = onion_dict_to_json(jres);
		onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
		onion_dict_free(jres);
		onion_block_free(jresb);
		return OCS_PROCESSED;
	}

	// Return error for other cases
	else
	{
		onion_response_set_code(res, 405);
		onion_response_write0(res, API_BADMETHOD_JSON);
		return OCS_PROCESSED;
	}
}
