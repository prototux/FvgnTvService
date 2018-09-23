#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>

#include <fpp/fpp.h>

uint8_t platform_power_current_fakeoff = 0;

uint8_t platform_power_fakeoff(uint8_t enabled)
{
	if (enabled)
	{
		fpp_graphics_mute(1);
		fpp_video_mute(1);
		fpp_power_set_backlight(0);
		fpp_panel_power_on_off(0);
	}
	else
	{
		fpp_panel_power_on_off(1);
		fpp_power_set_backlight(1);
		fpp_video_mute(0);
	}
	platform_power_current_fakeoff = enabled;
	return 0;
}

