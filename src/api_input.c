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

onion_connection_status api_input(void *unused, onion_request *req, onion_response *res)
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage POST case: Set input
	if ((flags & OR_METHODS) == OR_POST)
	{
		// Try to get POST data and parse json from it
		const onion_block *dreq = onion_request_get_data(req);
		onion_dict *jreq = NULL;
		if (dreq)
			jreq = onion_dict_from_json(onion_block_data(dreq));
		if (jreq)
		{
			if (!onion_dict_get(jreq, "input"))
			{
				onion_response_set_code(res, 500);
				onion_response_write0(res, "{\"status\":\"error\",\"message\":\"missing mandatory param input\"}");
				return OCS_PROCESSED;
			}

			// Get the ID, check the input, switch to it if correct
			uint32_t id = platform_input_get_id_from_name(onion_dict_get(jreq, "input"));
			if (!platform_input_is_enabled(id))
			{
				onion_response_set_code(res, 500);
				onion_response_write0(res, "{\"status\":\"error\",\"message\":\"input non existent or disabled\"}");
				return OCS_PROCESSED;
			}
			platform_input_switch_to(id);

			// Build response dict
			onion_dict *jres = onion_dict_new();
			onion_dict_add(jres, "status", "success", 0);
			onion_dict_add(jres, "input", platform_input_get_name_from_id(platform_input_current_linein), 0);

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

	// Manage GET case: get current input infos
	else if ((flags & OR_METHODS) == OR_GET)
	{
		onion_dict *jres = onion_dict_new();

		// name
		onion_dict_add(jres, "name", platform_input_get_name_from_id(platform_input_current_linein), 0);

		// plugged
		onion_dict_add(jres, "plugged", (platform_input_get_status(platform_input_current_linein))?"plugged":"unplugged", 0);

		// Get format infos
		struct fpp_signal_format format;
		platform_input_get_format(platform_input_current_linein, &format);

		// size
		onion_dict *resolution = onion_dict_new();
		api_dict_add_uint16(resolution, "width", format.width);
		api_dict_add_uint16(resolution, "height", format.height);
		onion_dict_add(jres, "size", resolution, OD_DICT);

		// framerate
		api_dict_add_uint8(jres, "framerate", format.framerate);

		// interlaced
		onion_dict_add(jres, "interlaced", (format.interlaced)?"yes":"no", 0);

		// dvi
		onion_dict_add(jres, "dvi", (format.dvi)?"yes":"no", 0);

		// analog_frequency
		for (int i = 0; i < PLATFORM_INPUTS_COUNT; i++)
			if (platform_inputs[i].id == platform_input_current_linein && platform_inputs[i].analog)
				api_dict_add_uint16(jres, "frequency", platform_input_get_analog_frequency(platform_input_current_linein));

		// vga
		if (platform_input_current_linein == LINEIN_PC1 || platform_input_current_linein == LINEIN_PC2)
		{
			uint16_t hpos, vpos, clock, phase;
			platform_input_get_vga_infos(&hpos, &vpos, &clock, &phase);
			onion_dict *vga = onion_dict_new();
			api_dict_add_uint16(vga, "hpos", hpos);
			api_dict_add_uint16(vga, "vpos", vpos);
			api_dict_add_uint16(vga, "clock", clock);
			api_dict_add_uint16(vga, "phase", phase);
			onion_dict_add(jres, "vga", vga, OD_DICT);
		}

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

onion_connection_status api_input_plugged(void *unused, onion_request *req, onion_response *res)
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage GET case: get plugged inputs
	if ((flags & OR_METHODS) == OR_GET)
	{
		onion_dict *jres = onion_dict_new();

		// Enumerate each input, and it's plugged/unplugged state
		for (int i = 0; i < PLATFORM_INPUTS_COUNT; i++)
			if (platform_inputs[i].enabled)
				onion_dict_add(jres, platform_inputs[i].name, (platform_input_get_status(platform_inputs[i].id))?"plugged":"unplugged", 0);

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
