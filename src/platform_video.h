#ifndef __PLATFORM_VIDEO_H__
#define __PLATFORM_VIDEO_H__

#include <fpp/fpp.h>

// Current video settings
extern uint8_t platform_video_brightness;
extern uint8_t platform_video_contrast;
extern uint8_t platform_video_saturation;
extern uint8_t platform_video_hue;
extern uint8_t platform_video_sharpness;
extern uint8_t platform_video_mute_red;
extern uint8_t platform_video_mute_green;
extern uint8_t platform_video_mute_blue;
extern uint8_t platform_video_muted;
extern uint8_t platform_video_frozen;
extern uint8_t platform_video_backlight;
extern uint8_t platform_video_noise_reduction;
extern uint8_t platform_video_black_stretch;
extern uint8_t platform_video_gamma;
extern uint8_t platform_video_current_film_mode;
extern uint8_t platform_video_dynamic_contrast;
extern uint8_t platform_video_current_flesh_tone;
extern uint8_t platform_video_current_game_mode;
extern uint16_t platform_video_white_balance[6];
extern uint8_t platform_video_current_black_stretch;
extern uint8_t platform_video_current_noise_reduction;
extern uint8_t platform_video_current_mpeg_nr;

extern char *platform_video_black_stretch_def[];
extern char *platform_video_noise_reduction_def[];
extern char *platform_video_mpeg_nr_def[];

// Error codes
#define E_FPPRET 1
#define E_OUTOFBOUNDS 2

// Functions
uint8_t platform_video_set_brightness(uint8_t value);
uint8_t platform_video_set_contrast(uint8_t value);
uint8_t platform_video_set_saturation(uint8_t value);
uint8_t platform_video_set_hue(uint8_t value);
uint8_t platform_video_set_sharpness(uint8_t value);
uint8_t platform_video_set_mute_color(uint8_t red, uint8_t green, uint8_t blue);
uint8_t platform_video_mute(uint8_t muted);
uint8_t platform_video_freeze(uint8_t frozen);
uint8_t platform_video_set_backlight(uint8_t value);
uint8_t platform_video_set_noise_reduction(uint8_t value);
uint8_t platform_video_set_black_stretch(uint8_t value);
uint8_t platform_video_set_gamma(uint8_t value);
uint8_t platform_video_enable_film_mode(uint8_t enabled);
uint8_t platform_video_enable_dynamic_contrast(uint8_t enabled);
uint8_t platform_video_set_mpeg_noise_reduction(enum fpp_mpeg_noise_reduction level);
uint8_t platform_video_enable_flesh_tone(uint8_t enabled);
uint8_t platform_video_enable_game_mode(uint8_t enabled);
//int platform_video_set_color_param(enum color_param param);
uint8_t platform_video_set_white_balance(uint16_t r_gain, uint16_t r_offset, uint16_t g_gain, uint16_t g_offset, uint16_t b_gain, uint16_t b_offset);
uint8_t platform_video_get_blackfield_status();
void platform_get_framerate(uint8_t *framerate);
void platform_get_video_size(uint8_t linein, uint16_t *width, uint16_t *height);
uint8_t platform_video_set_color_param(enum fpp_color_param param);

#endif /* __PLATFORM_VIDEO_H__ */
