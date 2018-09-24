#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>

#include <fpp/fpp.h>
#include "platform.h"

void platform_window_crop(uint32_t linein, uint32_t start_x, uint32_t start_y, uint32_t width, uint32_t height)
{
	struct fpp_signal_format format;
	platform_input_get_format(linein, &format);
	fpp_zoom_set_crop_window(linein, &format, start_x, start_y, width, height);
}

void platform_window_pos(uint32_t linein, uint32_t pos_x, uint32_t pos_y, uint32_t width, uint32_t height)
{
	struct fpp_signal_format format;
	platform_input_get_format(linein, &format);
	fpp_zoom_set_display_window(linein, &format, pos_x, pos_y, width, height);
	fpp_zoom_set_aspect_ratio(0);
}
