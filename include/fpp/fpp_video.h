/**
 * @file fpp_video.h
 * Management of video parameters
 */
#ifndef __FPP_VIDEO_H__
#define __FPP_VIDEO_H__

#include <inttypes.h>

/**
 * @brief A video adjustement item
 */
struct fpp_video_adj {
	uint8_t value;
	uint8_t min;
	uint8_t low;
	uint8_t mid;
	uint8_t high;
	uint8_t max;
	uint8_t reserved[2];
};

/**
 * @brief MPEG noise reduction level
 */
enum fpp_mpeg_noise_reduction {
	mpeg_nr_off,
	mpeg_nr_low,
	mpeg_nr_mid,
	mpeg_nr_high,
	mprg_nr_num
};

/**
 * @brief Black stretch level (still to confirm)
 */
enum fpp_black_stretch {
	stretch_off,
	stretch_dark,
	stretch_darker,
	stretch_darkest
};

/**
 * @brief Noise reduction level (still to confirm)
 */
enum fpp_noise_reduction {
	nr_off,
	nr_low,
	nr_mid,
	nr_high,
	nr_auto
};

/**
 * @brief Color space setting (still to confirm)
 */
enum fpp_color_space {
	color_space_auto,
	color_space_native,
	color_space_custom
};

/**
 * @brief Color warmth setting (still to confirm)
 */
enum fpp_color_warmth {
	color_warmth_cold,
	color_warmth_standard,
	color_warmth_warm,
	color_warmth_custom
};

/**
 * @brief Color parameter (preset?)
 */
enum fpp_color_param {
	EN_VIDEO_COLOR_NORMAL,
	EN_VIDEO_COLOR_ENHANCE_WIDE,
	EN_VIDEO_COLOR_XVYCC,
	EN_VIDEO_COLOR_BYPASS = 255,
	EN_VIDEO_COLOR_MAX
};

/**
 * fpp_video_decode_getPts is not documented yet.
 */
//void fpp_video_decode_getPts(void);

/**
 * fpp_video_decode_pushData is not documented yet.
 */
//void fpp_video_decode_pushData(void);

/**
 * @brief Enable/Disable dynamic contrast adjustement
 */
void fpp_video_enable_dynamic_contrast(uint8_t enabled);

/**
 * @brief Enable/Disable film mode, should "enhance" DVD/480p mpeg...
 */
void fpp_video_enable_film_mode(uint8_t enabled);

/**
 * @brief Freezes the video to current frame
 * @param freeze freeze (1) or unfreeze (0) the video
 */
void fpp_video_freeze(int freeze);

/**
 * @brief Get the background light
 */
void fpp_video_get_background_light(void);

/**
 * @brief Get black field status (???)
 */
void fpp_video_get_black_field_status(uint8_t *status);

/**
 * @brief Inits the video subsystem.
 */
void fpp_video_init(void);

/**
 * @brief Mute the video output (set panel to mute_color)
 * @param mute mute (1) or unmute (0) the video
 */
void fpp_video_mute(int mute);

/**
 * fpp_video_out_mute_output is not documented yet.
 */
//void fpp_video_out_mute_output(void);

/**
 * @brief Set the backlight level
 */
void fpp_video_set_background_light(struct fpp_video_adj adj);

/**
 * @brief Set the black stretch, should make dark colors darker
 */
void fpp_video_set_black_stretch(enum fpp_black_stretch);

/**
 * @brief Set video brightness
 * @param unknown Unknown, set to 1 when called from sita, 0 from libfpp
 * @param adj A video adjustement struct that contains the values, low and high are ignored.
 */
int fpp_video_set_brightness(uint8_t unknown, struct fpp_video_adj adj);

/**
 * @brief Set the color mode
 */
void fpp_video_set_color_param(enum fpp_color_param param);

/**
 * fpp_video_set_colorspace is not documented yet.
 */
//void fpp_video_set_colorspace(void);

/**
 * fpp_video_set_color_warmth is not documented yet.
 */
//void fpp_video_set_color_warmth(void);

/**
 * fpp_video_set_contrast is not documented yet.
 */
//void fpp_video_set_contrast(void);

/**
 * fpp_video_set_filterwindow is not documented yet.
 */
//void fpp_video_set_filterwindow(void);

/**
 * @brief Enable/Disable flesh tone "enhancement" (makes white skin more red)
 */
void fpp_video_set_flesh_tone(uint8_t enabled);

/**
 * @brief Enable/Disable game mode (should have less lag but less quality also)
 */
void fpp_video_set_game_mode(uint8_t enabled);

/**
 * @brief Set gamma (between 1 and 6)
 */
void fpp_video_set_gamma(uint8_t value);

/**
 * fpp_video_set_gamma_10p is not documented yet.
 */
//void fpp_video_set_gamma_10p(void);

/**
 * @brief Set hue
 */
void fpp_video_set_hue(uint8_t unknown, struct fpp_video_adj adj);

/**
 * @brief Reduces MPEG compression noise/artifacts
 */
void fpp_video_set_mpeg_nr(enum fpp_mpeg_noise_reduction);

/**
 * @brief Set the video mute color
 * @param red Red quanity
 * @param green Green quantity
 * @param blue Blue quantity
 */
void fpp_video_set_mute_color(uint8_t red, uint8_t green, uint8_t blue);

/**
 * fpp_video_set_noise_reduction is not documented yet.
 */
void fpp_video_set_noise_reduction(enum fpp_noise_reduction value);

/**
 * fpp_video_set_pq_algorithm is not documented yet.
 */
//void fpp_video_set_pq_algorithm(void);

/**
 * @brief Set saturation
 */
void fpp_video_set_saturation(uint8_t unknown, struct fpp_video_adj adj);

/**
 * @brief Set sharpness
 */
void fpp_video_set_sharpness(uint8_t unknown, struct fpp_video_adj adj);

/**
 * @brief Turns ON or OFF the backlight
 * @param enable Turn ON (1) or OFF (0) the backlight
 */
void fpp_video_turn_on_backlight(int enable);

#endif /* __FPP_VIDEO_H__ */
