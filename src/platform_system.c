#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>

#include <fpp/fpp.h>

void platform_system_enter_4k2k_mode()
{
	fpp_system_enter_4k2k_mode(MODE_4K2K);
}

void platform_system_exit_4k2k_mode()
{
	fpp_system_enter_4k2k_mode(MODE_4K2K);
}

enum fpp_system_soc_mode platform_system_is_4k2k_mode()
{
	enum fpp_system_soc_mode mode;
	fpp_system_is_4k2k_mode(&mode);
	return mode;
}

void platform_system_enter_debug_menu()
{
	fpp_system_fpp_debug_switch(1, 1);
}
