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

void platform_power_poweroff()
{
	fpp_power_off(1);
}

uint8_t platform_power_get_led()
{
	// status: 0 off, 1 on, 2 breathing, 3 flashing ?
	// Stack smashing it isn't a uint32_t, what?
	uint32_t status = 0;
	fpp_power_get_led_status(2, (uint8_t*)&status);
	printf("LED Status: %d\n", status);
	return (uint8_t)status;
}

// LED 0 (standby led) doesn't exist on my hardware...
// So we only use LED 2 ("work" led)
void platform_power_set_led(uint8_t status)
{
	fpp_power_set_led_status(2, status);
}

uint8_t platform_power_get_backlight()
{
	uint8_t enabled;
	fpp_power_get_backlight(&enabled);
	return enabled;
}
