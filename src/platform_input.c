#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <fpp/fpp.h>

uint8_t platform_input_get_current()
{
	return 0;
}

void platform_input_get_video_size(uint32_t linein, uint16_t *width, uint16_t *height)
{
    fpp_signal_get_video_size(linein, 0, width, height);
}

uint16_t platform_input_get_framerate(uint32_t linein)
{
	struct fpp_signal_format_short format;
	uint32_t id;
	fpp_signal_get_format(linein, &id, &format);
	printf("format: %dx%d*%d\n", format.width, format.height, format.framerate);
	return format.framerate/100;
}

uint16_t platform_input_get_analog_frequency(uint32_t linein)
{
	uint16_t frequency;
	fpp_signal_get_frequncy(linein, &frequency);
	return frequency;
}

uint16_t platform_input_get_color_space(uint32_t linein)
{
	uint16_t color_space;
	fpp_signal_get_color_space(linein, 0, &color_space);
	return color_space;
}


uint8_t platform_input_get_status(uint32_t linein)
{
	uint8_t status;
	fpp_linein_src_insert_check(linein, &status);
	printf("Status: %d\n", status);
	return status;
}
