#ifndef __PLATFORM_INIT_H__
#define __PLATFORM_INIT_H__

struct platform_config_def {
	struct {
		char *input;
		char *model;
		char *config_0;
		char *config_1;
		char *config_6;
		char *config_8;
		char *config_7;
		char *config_16;
		char *pq_path;
		char *pq_patch;
		char *panel;
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
};
extern struct platform_config_def platform_config;

int platform_init_config();
int platform_init_fpp();
int platform_init_video(void);

#endif /* __PLATFORM_INIT_H__ */
