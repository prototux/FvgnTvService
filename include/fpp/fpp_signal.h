/**
 * @file fpp_signal.h
 * fpp_signal is not defined yet
 */
#ifndef __FPP_SIGNAL_H__
#define __FPP_SIGNAL_H__

/**
 * @brief Signal format long definition
 */
struct fpp_signal_format {
	uint32_t format_id;
	uint32_t width;
	uint32_t height;
	uint8_t color_space;
	uint8_t dvi;
	uint8_t framerate;
	uint8_t interlaced;
};

/**
 * @brief Signal format short definition
 */
struct fpp_signal_format_short {
	uint16_t width;
	uint16_t height;
	uint16_t framerate;
	uint8_t interlaced;
	uint8_t reserved[3];
};

/**
 * fpp_signal_check_routine is not documented yet.
 */
void fpp_signal_check_routine(void);

/**
 * @brief Get the current color space
 * @param linein linein to get the color space from
 * @param reserver unknown, alaway set to 0
 * @param color_space pointer to an uin8_t to the color space to
 */
void fpp_signal_get_color_space(uint8_t linein, uint8_t reserved, uint8_t *color_space);

/**
 * fpp_signal_get_color_system is not documented yet.
 */
void fpp_signal_get_color_system(void);

/**
 * fpp_signal_get_disp_framerate is not documented yet.
 */
//void fpp_signal_get_disp_framerate(void);

/**
 * fpp_signal_get_format is not documented yet.
 */
//void fpp_signal_get_format(void);

/**
 * fpp_signal_get_frequncy is not documented yet.
 */
//void fpp_signal_get_frequncy(void);

/**
 * fpp_signal_get_hdmi_provider_type is not documented yet.
 */
//void fpp_signal_get_hdmi_provider_type(void);

/**
 * fpp_signal_get_info is not documented yet.
 */
void fpp_signal_get_info(void);

/**
 * fpp_signal_get_lock_state is not documented yet.
 */
void fpp_signal_get_lock_state(void);

/**
 * fpp_signal_get_sound_system is not documented yet.
 */
void fpp_signal_get_sound_system(void);

/**
 * fpp_signal_get_video_size is not documented yet.
 */
//void fpp_signal_get_video_size(void);

/**
 * fpp_signal_get_wss is not documented yet.
 */
void fpp_signal_get_wss(void);

/**
 * fpp_signal_is_dvi is not documented yet.
 */
void fpp_signal_is_dvi(void);

/**
 * fpp_signal_is_interlaced is not documented yet.
 */
void fpp_signal_is_interlaced(void);

/**
 * fpp_signal_monitor_afd_change is not documented yet.
 */
void fpp_signal_monitor_afd_change(void);

/**
 * fpp_signal_monitor_exinit is not documented yet.
 */
//void fpp_signal_monitor_exinit(void);

/**
 * fpp_signal_monitor_formatchange is not documented yet.
 */
//void fpp_signal_monitor_formatchange(void);

/**
 * fpp_signal_monitor_init is not documented yet.
 */
//void fpp_signal_monitor_init(void);

/**
 * fpp_signal_monitor_lock is not documented yet.
 */
//void fpp_signal_monitor_lock(void);

/**
 * fpp_signal_monitor_scart_change is not documented yet.
 */
void fpp_signal_monitor_scart_change(void);

/**
 * fpp_signal_monitor_src_insert is not documented yet.
 */
void fpp_signal_monitor_src_insert(void);

/**
 * fpp_signal_monitor_unlock is not documented yet.
 */
//void fpp_signal_monitor_unlock(void);

/**
 * fpp_signal_monitor_wss_change is not documented yet.
 */
void fpp_signal_monitor_wss_change(void);

/**
 * fpp_signal_set_color_system is not documented yet.
 */
void fpp_signal_set_color_system(void);

/**
 * fpp_signal_set_hdmi_provider_type is not documented yet.
 */
//void fpp_signal_set_hdmi_provider_type(void);

/**
 * fpp_signal_set_sound_system is not documented yet.
 */
void fpp_signal_set_sound_system(void);

#endif /* __FPP_SIGNAL_H__ */
