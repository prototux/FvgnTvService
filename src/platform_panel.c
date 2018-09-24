#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>

#include <fpp/fpp.h>

void platform_panel_get_resolution(uint16_t *width, uint16_t *height)
{
	struct fpp_resolution infos;
	fpp_system_get_panel_resolution(&infos);
	*width = infos.width;
	*height = infos.height;
}

uint8_t platform_panel_get_average_luma()
{
	uint8_t luma;
	fpp_system_get_average_luma(&luma);
	return luma;
}

uint8_t platform_panel_get_luma_distribution(uint16_t *results)
{
	uint8_t size = 32;
	fpp_system_get_luma_level_distribution(results, size);
	return size;
}

uint8_t platform_panel_set_video_mirror(uint8_t enabled)
{
	fpp_system_panel_set_video_mirror(enabled);
	return enabled;
}

uint8_t platform_panel_set_osd_mirror(uint8_t enabled)
{
	fpp_system_panel_set_osd_mirror(enabled);
	return enabled;
}
