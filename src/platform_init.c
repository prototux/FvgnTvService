#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>

#include <fpp/fpp.h>
#include <inih/ini.h>
#include "platform.h"

struct {
	struct {
		char *input;
		char *config_0;
		char *config_1;
		char *config_6;
		char *config_8;
		char *config_7;
		char *config_16;
		char *pq_path;
		char *pq_patch;
		char *panel
	} system;

	struct {
		uint8_t brightness;
		uint8_t contrast;
		uint8_t saturation;
		uint8_t hue;
		uint8_t sharpness;
		uint8_t backlight;
		uint8_t gamma;
		uint8_t dynamic_contrast;
		uint8_t film_mode;
		uint8_t game_mode;
		uint8_t flesh_tone;
		uint8_t black_stretch;
		uint8_t noise_reduction;
		uint8_t mpeg_nr;
		uint8_t video_mirror;
		uint8_t osd_mirror;
	} video;
} platform_config;

static int platform_init_config_parse(void* user, const char* section, const char* name, const char* value)
{
	printf("=> Parsing %s.%s (=%s)\n", section, name, value);
	if (!strcmp(section, "system"))
	{
		if (!strcmp(name, "input"))
			platform_config.system.input = strdup(value);
		else if (!strcmp(name, "config_0"))
			platform_config.system.config_0 = strdup(value);
		else if (!strcmp(name, "config_1"))
			platform_config.system.config_1 = strdup(value);
		else if (!strcmp(name, "config_6"))
			platform_config.system.config_6 = strdup(value);
		else if (!strcmp(name, "config_8"))
			platform_config.system.config_8 = strdup(value);
		else if (!strcmp(name, "config_7"))
			platform_config.system.config_7 = strdup(value);
		else if (!strcmp(name, "config_16"))
			platform_config.system.config_16 = strdup(value);
		else if (!strcmp(name, "panel"))
			platform_config.system.panel = strdup(value);
		else if (!strcmp(name, "pq_path"))
			platform_config.system.pq_path = strdup(value);
		else if (!strcmp(name, "pq_patch"))
			platform_config.system.pq_patch = strdup(value);
	}
	else if (!strcmp(section, "video"))
	{
		if (!strcmp(name, "brightness"))
			platform_config.video.brightness = atoi(value);
		else if (!strcmp(name, "contrast"))
			platform_config.video.contrast = atoi(value);
		else if (!strcmp(name, "saturation"))
			platform_config.video.saturation = atoi(value);
		else if (!strcmp(name, "hue"))
			platform_config.video.hue = atoi(value);
		else if (!strcmp(name, "sharpness"))
			platform_config.video.sharpness = atoi(value);
		else if (!strcmp(name, "backlight"))
			platform_config.video.backlight = atoi(value);
		else if (!strcmp(name, "gamma"))
			platform_config.video.gamma = atoi(value);
		else if (!strcmp(name, "dynamic_contrast"))
			platform_config.video.dynamic_contrast = atoi(value);
		else if (!strcmp(name, "film_mode"))
			platform_config.video.film_mode = atoi(value);
		else if (!strcmp(name, "game_mode"))
			platform_config.video.game_mode = atoi(value);
		else if (!strcmp(name, "flesh_tone"))
			platform_config.video.flesh_tone = atoi(value);
		else if (!strcmp(name, "black_stretch"))
			platform_config.video.black_stretch = atoi(value);
		else if (!strcmp(name, "noise_reduction"))
			platform_config.video.noise_reduction = atoi(value);
		else if (!strcmp(name, "mpeg_nr"))
			platform_config.video.mpeg_nr = atoi(value);
		else if (!strcmp(name, "video_mirror"))
			platform_config.video.video_mirror = atoi(value);
		else if (!strcmp(name, "osd_mirror"))
			platform_config.video.osd_mirror = atoi(value);
	}
	else
		return 0;
	return 1;
}

int platform_init_config()
{
	char *config_path = (getenv("FVGN_CONFIG"))?getenv("FVGN_CONFIG"):"/etc/fvgntvservice.conf";
	printf("Reading config at %s\n", config_path);

	if (ini_parse(config_path, platform_init_config_parse, NULL) < 0)
	{
		printf("Cannot read config!\n");
		return 0;
	}
	printf("Done reading config\n");
	return 1;
}

int platform_init_fpp()
{
	// Check that we have the config item we need
	if (!platform_config.system.config_0 || !platform_config.system.config_1 || !platform_config.system.config_6 || !platform_config.system.config_8 || !platform_config.system.config_7 || !platform_config.system.config_16 || !platform_config.system.panel || !platform_config.system.pq_path || !platform_config.system.pq_patch)
	{
		printf("Config items not set, abort.\n");
		return 0;
	}

	// Configuration items
	struct platform_config_item
	{
		unsigned int id;
		char *path;
	} config_items[6] = {
		{.id = 0, .path = platform_config.system.config_0},
		{.id = 1, .path = platform_config.system.config_1},
		{.id = 6, .path = platform_config.system.config_6},
		{.id = 8, .path = platform_config.system.config_8},
		{.id = 7, .path = platform_config.system.config_7},
		{.id = 16, .path = platform_config.system.config_16}
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
    fpp_system_set_pq_dir_path(platform_config.system.pq_path, platform_config.system.pq_patch);

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
	fpp_system_set_panel_file_name(platform_config.system.panel);

	// Disable the watchdog
	fpp_factory_watch_dog_operate(WATCHDOG_DISABLE);

	// Wait a bit for it to be really init
	usleep(400000);
	return 1;
}

int platform_init_video(void)
{
	if (!platform_config.system.input)
	{
		printf("No default input!\n");
		return 0;
	}

	// Switch to the correct video input
	printf("Open default input (%s)\n", platform_config.system.input);
	platform_input_switch_to(platform_input_get_id_from_name(platform_config.system.input));
	printf("Done opening default input\n");

	// Set brightness
	printf("Setting default brightness (%d)\n", platform_config.video.brightness);
	platform_video_set_brightness(platform_config.video.brightness);

	// Set contrast
	printf("Setting default contrast (%d)\n", platform_config.video.contrast);
	platform_video_set_contrast(platform_config.video.contrast);

	// Set saturation
	printf("Setting default saturation (%d)\n", platform_config.video.saturation);
	platform_video_set_saturation(platform_config.video.saturation);

	// Set hue
	printf("Setting default hue (%d)\n", platform_config.video.hue);
	platform_video_set_hue(platform_config.video.hue);

	// Set sharpness
	printf("Setting default sharpness (%d)\n", platform_config.video.sharpness);
	platform_video_set_sharpness(platform_config.video.sharpness);

	// Set backlight
	printf("Setting default backlight (%d)\n", platform_config.video.backlight);
	platform_video_set_backlight(platform_config.video.backlight);

	// Set gamma
	printf("Setting default gamma (%d)\n", platform_config.video.gamma);
	platform_video_set_gamma(platform_config.video.gamma);

	// Set dynamic_contrast
	printf("Setting default dynamic_contrast (%d)\n", platform_config.video.dynamic_contrast);
	platform_video_enable_dynamic_contrast(platform_config.video.dynamic_contrast);

	// Set film_mode
	printf("Setting default film_mode (%d)\n", platform_config.video.film_mode);
	platform_video_enable_film_mode(platform_config.video.film_mode);

	// Set game_mode
	printf("Setting default game_mode (%d)\n", platform_config.video.game_mode);
	platform_video_enable_game_mode(platform_config.video.game_mode);

	// Set flesh_tone
	printf("Setting default flesh_tone (%d)\n", platform_config.video.flesh_tone);
	platform_video_enable_flesh_tone(platform_config.video.flesh_tone);

	// Set black_stretch
	printf("Setting default black_stretch (%d)\n", platform_config.video.black_stretch);
	platform_video_set_black_stretch(platform_config.video.black_stretch);

	// Set noise_reduction
	printf("Setting default noise_reduction (%d)\n", platform_config.video.noise_reduction);
	platform_video_set_noise_reduction(platform_config.video.noise_reduction);

	// Set mpeg_nr
	printf("Setting default mpeg_nr (%d)\n", platform_config.video.mpeg_nr);
	platform_video_set_mpeg_noise_reduction(platform_config.video.mpeg_nr);

	// Set video_mirror
	printf("Setting default video_mirror (%d)\n", platform_config.video.video_mirror);
	platform_panel_set_video_mirror(platform_config.video.video_mirror);

	// Set osd_mirror
	printf("Setting default osd_mirror (%d)\n", platform_config.video.osd_mirror);
	platform_panel_set_osd_mirror(platform_config.video.osd_mirror);

    // Turn on panel, unmute video, mute graphics
    fpp_panel_power_on_off(1);
    fpp_graphics_mute(1);
    fpp_power_set_backlight(1);
	usleep(400000);
	return 1;
}
