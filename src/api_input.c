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

struct input_def {
	char *key;
	uint32_t value;
} inputs[] = {
	{ "hdmi-1", LINEIN_HDMI1 },
	{ "hdmi-2", LINEIN_HDMI2 },
	{ "hdmi-3", LINEIN_HDMI3 },
	{ "hdmi-4", LINEIN_HDMI4 },
	{ "composite-1", LINEIN_CVBS1 },
	{ "composite-2", LINEIN_CVBS2 },
	{ "composite-3", LINEIN_CVBS3 },
	{ "composite-4", LINEIN_CVBS4 },
	{ "svideo-1", LINEIN_SVIDEO1 },
	{ "svideo-2", LINEIN_SVIDEO2 },
	{ "component-1", LINEIN_COMPONENT1 },
	{ "component-2", LINEIN_COMPONENT2 },
	{ "component-3", LINEIN_COMPONENT3 },
	{ "component-4", LINEIN_COMPONENT4 },
	{ "vga-1", LINEIN_PC1 },
	{ "vga-2", LINEIN_PC2 },
	{ "scart-1", LINEIN_SCART1 },
	{ "scart-2", LINEIN_SCART2 }
};

#define NB_INPUTS 18

uint32_t platform_input_get_id_from_name(char *name)
{
	for (int i = 0; i < NB_INPUTS; i++)
		if (!strcmp(inputs[i].key, name))
			return inputs[i].value;
	return 0;
}

char *platform_input_get_name_from_id(uint32_t id)
{
	for (int i = 0; i < NB_INPUTS; i++)
		if (inputs[i].value == id)
			return inputs[i].key;
	return 0;
}

onion_connection_status api_input(void *unused, onion_request *req, onion_response *res)
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
			if (onion_dict_get(jreq, "input"))
				platform_input_switch_to(platform_input_get_id_from_name(onion_dict_get(jreq, "input")));

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

	// Manage GET case: get current status and color
	else if ((flags & OR_METHODS) == OR_GET)
	{
		onion_dict *jres = onion_dict_new();

		// name
		onion_dict_add(jres, "name", platform_input_get_name_from_id(platform_input_current_linein), 0);

		// plugged
		onion_dict_add(jres, "plugged", (platform_input_get_status(LINEIN_HDMI4))?"plugged":"unplugged", 0);

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
		// TODO
		// vga
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

onion_connection_status api_input_plugged(void *unused, onion_request *req, onion_response *res)
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage GET case: get system infos
	if ((flags & OR_METHODS) == OR_GET)
	{
		onion_dict *jres = onion_dict_new();

		// HDMI
		onion_dict_add(jres, "hdmi-1", (platform_input_get_status(LINEIN_HDMI1))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "hdmi-2", (platform_input_get_status(LINEIN_HDMI2))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "hdmi-3", (platform_input_get_status(LINEIN_HDMI3))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "hdmi-4", (platform_input_get_status(LINEIN_HDMI4))?"plugged":"unplugged", 0);

		// Composite & S-Video
		onion_dict_add(jres, "composite-1", (platform_input_get_status(LINEIN_CVBS1))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "composite-2", (platform_input_get_status(LINEIN_CVBS2))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "composite-3", (platform_input_get_status(LINEIN_CVBS3))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "composite-4", (platform_input_get_status(LINEIN_CVBS4))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "svideo-1", (platform_input_get_status(LINEIN_SVIDEO1))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "svideo-2", (platform_input_get_status(LINEIN_SVIDEO2))?"plugged":"unplugged", 0);

		// Component
		onion_dict_add(jres, "component-1", (platform_input_get_status(LINEIN_COMPONENT1))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "component-2", (platform_input_get_status(LINEIN_COMPONENT2))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "component-3", (platform_input_get_status(LINEIN_COMPONENT3))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "component-4", (platform_input_get_status(LINEIN_COMPONENT4))?"plugged":"unplugged", 0);

		// VGA
		onion_dict_add(jres, "vga-1", (platform_input_get_status(LINEIN_PC1))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "vga-2", (platform_input_get_status(LINEIN_PC2))?"plugged":"unplugged", 0);

		// SCART
		onion_dict_add(jres, "scart-1", (platform_input_get_status(LINEIN_SCART1))?"plugged":"unplugged", 0);
		onion_dict_add(jres, "scart-1", (platform_input_get_status(LINEIN_SCART2))?"plugged":"unplugged", 0);

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
