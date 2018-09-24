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


onion_connection_status api_process_linear(onion_request *req, onion_response *res, uint8_t *current_value, int (*set_function)(uint8_t))
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage POST case: change the value
	if ((flags & OR_METHODS) == OR_POST)
	{
		// Try to get POST data and parse json from it
		const onion_block *dreq = onion_request_get_data(req);
		onion_dict *jreq = NULL;
		if (dreq)
			jreq = onion_dict_from_json(onion_block_data(dreq));
		if (jreq)
		{
			// Get and set the value
			int value = atoi(onion_dict_get(jreq, "value"));
			(*set_function)(value);

			// Build response dict
			char value_str[4];
			snprintf(value_str, 4, "%d", *current_value);
			onion_dict *jres = onion_dict_new();
			onion_dict_add(jres, "status", "success", 0);
			onion_dict_add(jres, "value", &value_str, 0);

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

	// Manage GET case: get value
	else if ((flags & OR_METHODS) == OR_GET)
	{
		char value_str[4];
		snprintf(value_str, 4, "%d", *current_value);
		onion_dict *jres = onion_dict_new();
		onion_dict_add(jres, "value", &value_str, 0);
		onion_block *jresb = onion_dict_to_json(jres);
		onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
		onion_block_free(jresb);
		onion_dict_free(jres);
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

onion_connection_status api_process_bool(onion_request *req, onion_response *res, uint8_t *current_value, int (*set_function)(uint8_t))
{
	const onion_request_flags flags = onion_request_get_flags(req);

	// Manage POST case: change the value
	if ((flags & OR_METHODS) == OR_POST)
	{
		// Try to get POST data and parse json from it
		const onion_block *dreq = onion_request_get_data(req);
		onion_dict *jreq = NULL;
		if (dreq)
			jreq = onion_dict_from_json(onion_block_data(dreq));
		if (jreq)
		{
			// Get and set the value
			int enabled = atoi(onion_dict_get(jreq, "enabled"));
			(*set_function)(enabled);

			// Build response dict
			char *current = (*current_value)?"enabled":"disabled";
			onion_dict *jres = onion_dict_new();
			onion_dict_add(jres, "status", "success", 0);
			onion_dict_add(jres, "enabled", current, 0);

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

	// Manage GET case: get value
	else if ((flags & OR_METHODS) == OR_GET)
	{
		char *current = (*current_value)?"enabled":"disabled";
		onion_dict *jres = onion_dict_new();
		onion_dict_add(jres, "enabled", current, 0);
		onion_block *jresb = onion_dict_to_json(jres);
		onion_response_write(res, onion_block_data(jresb), onion_block_size(jresb));
		onion_block_free(jresb);
		onion_dict_free(jres);
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
