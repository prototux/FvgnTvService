#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>

#include <fpp/fpp.h>

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
}

void platform_init_video(void)
{
	platform_video_set_brightness(90);
	platform_video_set_contrast(80);
	platform_video_set_hue(50);
	platform_video_set_saturation(50);
	platform_video_set_sharpness(100);
	platform_video_set_backlight(100);
	platform_video_set_gamma(100);
	platform_video_set_white_balance(135, 128, 128, 128, 118, 128);

	// Disabled options
	platform_video_set_gamma(1);
	platform_video_enable_film_mode(0);
	platform_video_set_black_stretch(3);
	platform_video_set_noise_reduction(4);
	platform_video_enable_flesh_tone(0);
	platform_video_enable_game_mode(0);
}

void platform_test_callback(void)
{
	printf("==> Got signal change!\n");
	platform_video_mute(1);
	// test things
	uint32_t id, w, h, fr, il;
	struct test_format {
		uint16_t w;
		uint16_t h;
		uint16_t framerate;
		uint8_t interlaced;
		uint8_t reserved[3];
	};
	struct test_format format;
	fpp_signal_get_format(LINEIN_HDMI3, &id, &format);
	//fpp_signal_get_video_size(LINEIN_HDMI3, 0, &w, &h);
	printf("format: id=%d w=%d h=%d test=%d\n", id, format.w, format.h, format.framerate);
	//printf("Reso: %dx%d\n", w, h);

	//inutile xvycc + film framretate info? fpp_signal_get_info
	//inutile? fpp_signal_get_color_space
	//fpp_signal_get_frequency // seulement analog
	//inutile ?fpp_signal_get_sound_system
	//fpp_signal_get_hdmi_provider_type // auto-pc-video-max
	//fpp_signal_get_color_system // ??
	//fpp_signal_is_dvi // ??
	//fpp_signal_is_interlaced // ??
	int color_space = 0;
	fpp_signal_get_color_space(LINEIN_HDMI3, 0, &color_space);
	printf("color space: %d\n", color_space);

	//int disp_fr = 42;
	//fpp_signal_get_disp_framerate(&disp_fr);
	//printf("Display framerate %d\n", disp_fr);

	//int hdmi_type = 42;
	//fpp_signal_get_hdmi_provider_type(&hdmi_type);
	//printf("provider: %d\n", hdmi_type);
	//fpp_signal_set_hdmi_provider_type(0);


	//test set new size
	struct fpp_signal_format new_format = {
		.format_id = 0,
		.width = format.w,
		.height = format.h,
		.color_space = color_space,
		.dvi = 1,
		.framerate = 60,
		.interlaced = format.interlaced
	};
	fpp_hdmi_process_signal_formatchange(LINEIN_HDMI3, format);
	fpp_zoom_set_crop_window(LINEIN_HDMI3, &new_format, 0, 0, format.w, format.h);
	fpp_zoom_set_display_window(LINEIN_HDMI3, &new_format, 0, 0, 1920, 1080);
	usleep(100000);
	platform_video_mute(0);
	return 0;
}

void platform_open_hdmi(void)
{
    struct fpp_signal_format sig_format = {
        .format_id = 1,
        .width = 1920,
        .height = 1080,
        .color_space = 1,
        .dvi = 1,
        .framerate = 60,
        .interlaced = 0
    };

	// Hardcoded to hdmi3 for tests
	int current_linein = LINEIN_HDMI3;

	// Open the HDMI input and wait some time
	fpp_linein_open_hdmi(current_linein);
	usleep(300000);

	// Set the input window
	fpp_zoom_set_crop_window(current_linein, &sig_format, 0,0, 1920, 1080);
	fpp_zoom_set_display_window(current_linein, &sig_format, 0,0, 1920, 1080);

    // Turn on panel, unmute video, mute graphics
    fpp_panel_power_on_off(1);
    fpp_video_mute(0);
    fpp_graphics_mute(1);
    fpp_power_set_backlight(1);
	usleep(400000);


	// Test
	printf("insert? %d\n", platform_input_get_status(LINEIN_HDMI3));
	printf("framerate: %d\n", platform_input_get_framerate(LINEIN_HDMI3));
	// uninit?
	fpp_signal_monitor_exinit();
	// linein
	fpp_signal_monitor_init(LINEIN_HDMI3);
	// linein, enable?, callbackfunc
	fpp_signal_monitor_formatchange(LINEIN_HDMI3, 1, platform_test_callback);
}
