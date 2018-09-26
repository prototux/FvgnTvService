#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>

#include <fpp/fpp.h>
#include "platform.h"

void platform_init()
{
	// Configuration items
	struct platform_config_item
	{
		unsigned int id;
		char *path;
	} config_items[6] = {
		{.id = 0, .path = "/application/tclconfig/pq/ID87/"},
		{.id = 1, .path = "/appliations/tclconfig/pq/patch/"},
		{.id = 6, .path = "/applicaions/tclconfig/gamma/Gamma7_L32E4300CE.bin"},
		{.id = 8, .path = "/appications/tclconfig/EDID_BIN/HDMI_EDID_4K_NO3D.bin"},
		{.id = 7, .path = "/applicaions/tclconfig/EDID_BIN/VGA_EDID.bin"},
		{.id = 16, .path = "/aplications/tclconfig/audio/audioPP/audioPP_23.txt"}
	};

	// I don't know why, but that's needed
	static char platform_stbc_data[7168] = {0x54, 0x53, 0x43, 0x42, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};

	// fpp_driver parameters
	struct fpp_driver_parameters driver_para = {
		.os_type = OS_LINUX,
		.area = AREA_EU,
		.type = 0,
		.extend = &platform_stbc_data
	};

	// Init configuration items
    for (int i = 0; i < 6; i++)
        fpp_system_set_config_path_and_name(config_items[i].id, config_items[i].path, strlen(config_items[i].path));

    // Init pq dir path
    fpp_system_set_pq_dir_path("/applications/tclconfig/pq/ID87/", "/applications/tclconfig/pq/patch/");

    // Init driver
    fpp_driver_init(&driver_para);

    // Init GPIO
    fpp_gpio_init();

    // Init I2C
    fpp_iic_init();

    // Init Board IC (???) and SoC
    fpp_board_ic_init();
    fpp_board_soc_init(0);

    // Init video
    fpp_video_init();

    // Init RTC
    fpp_board_rtc_init();

	// Set panel file
	fpp_system_set_panel_file_name("/applications/tclconfig/panel/panel_64_3840_2160.txt");

	// Disable the watchdog
	fpp_factory_watch_dog_operate(WATCHDOG_DISABLE);

	// Wait a bit for it to be really init
	usleep(400000);
}

void platform_open_hdmi(void)
{
	// Switch to HDMI3 for test
	printf("Switch to hdmi3\n");
	platform_input_switch_to(LINEIN_HDMI3);
	printf("Done switching\n");

    // Turn on panel, unmute video, mute graphics
    fpp_panel_power_on_off(1);
    fpp_graphics_mute(1);
    fpp_power_set_backlight(1);
	usleep(400000);
}
