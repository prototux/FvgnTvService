#ifndef __PLATFORM_POWER_H__
#define __PLATFORM_POWER_H__

// Global variables
extern uint8_t platform_power_current_fakeoff;

// Functions
uint8_t platform_power_fakeoff(uint8_t enabled);
void platform_power_poweroff();
uint8_t platform_power_get_led();
void platform_power_set_led(uint8_t status);

#endif /* __PLATFORM_POWER_H__ */
