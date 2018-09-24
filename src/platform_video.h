#ifndef __PLATFORM_VIDEO_H__
#define __PLATFORM_VIDEO_H__

// Current video settings
extern uint8_t platform_video_brightness;
extern uint8_t platform_video_contrast;
extern uint8_t platform_video_saturation;
extern uint8_t platform_video_hue;
extern uint8_t platform_video_sharpness;
extern uint8_t platform_video_mute_color[3];
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

// Error codes
#define E_FPPRET 1
#define E_OUTOFBOUNDS 2

// Functions
int platform_video_set_brightness(uint8_t value);
int platform_video_set_contrast(uint8_t value);
int platform_video_set_saturation(uint8_t value);
int platform_video_set_hue(uint8_t value);
int platform_video_set_sharpness(uint8_t value);
int platform_video_set_mute_color(uint8_t red, uint8_t green, uint8_t blue);
int platform_video_mute(uint8_t muted);
int platform_video_freeze(uint8_t frozen);
int platform_video_set_backlight(uint8_t value);
int platform_video_set_noise_reduction(uint8_t value);
int platform_video_set_black_stretch(uint8_t value);
int platform_video_set_gamma(uint8_t value);
int platform_video_enable_film_mode(uint8_t enabled);
int platform_video_enable_dynamic_contrast(uint8_t enabled);
//int platform_video_set_mpeg_noise_reduction(enum mpeg_noise_reduction level);
int platform_video_enable_flesh_tone(uint8_t enabled);
int platform_video_enable_game_mode(uint8_t enabled);
//int platform_video_set_color_param(enum color_param param);
int platform_video_set_white_balance(uint16_t r_gain, uint16_t r_offset, uint16_t g_gain, uint16_t g_offset, uint16_t b_gain, uint16_t b_offset);


#endif /* __PLATFORM_VIDEO_H__ */