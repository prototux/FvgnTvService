#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>

#include <fpp/fpp.h>

void platform_system_enter_4k2k_mode()
{
	uint8_t mode = 0; // 0=E_MODE_4K2K, 1=E_MODE_MAX
	fpp_system_enter_4k2k_mode(mode);
}

void platform_system_exit_4k2k_mode()
{
	uint8_t mode = 0; // 0=E_MODE_4K2K, 1=E_MODE_MAX
	fpp_system_enter_4k2k_mode(mode);
}

uint8_t platform_system_is_4k2k_mode()
{
	uint8_t mode = 0; //E_SOC_OUT_MODE_4K2K, E_SOC_OUT_MODE_NORMAL, E_SOC_OUT_MODE_MAX
	fpp_system_is_4k2k_mode(&mode);
	return mode;
}

void platform_system_enter_debug_menu()
{
	fpp_system_fpp_debug_switch(1, 1);
}
