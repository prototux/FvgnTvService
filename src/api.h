#ifndef __API_ALL_H__
#define __API_ALL_H__

#include "api_audio.h"
#include "api_input.h"
#include "api_panel.h"
#include "api_power.h"
#include "api_system.h"
#include "api_video.h"
#include "api_zoom.h"

#define API_BADREQUEST_JSON "{\"error\": 400, \"message\": \"No data\"}"
#define API_BADMETHOD_JSON "{\"error\": 405, \"message\": \"Method not allowed\"}"

#endif /* __API_ALL_H__ */
