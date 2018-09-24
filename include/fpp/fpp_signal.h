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
 * @brief Types of hdmi provider (?)
 */
enum fpp_hdmi_provider_type {
	HDMI_PROVIDER_TYPE_AUTO,
	HDMI_PROVIDER_TYPE_PC,
	HDMI_PROVIDER_TYPE_VIDEO,
	HDMI_PROVIDER_TYPE_MAX
};

/**
 * @brief Types of sound system (?)
 */
enum fpp_sound_system {
	EN_AUDIOSTANDARD_BG_,
	EN_AUDIOSTANDARD_BG_A2_,
	EN_AUDIOSTANDARD_BG_NICAM_,
	EN_AUDIOSTANDARD_I_,
	EN_AUDIOSTANDARD_DK_,
	EN_AUDIOSTANDARD_DK1_A2_,
	EN_AUDIOSTANDARD_DK2_A2_,
	EN_AUDIOSTANDARD_DK3_A2_,
    EN_AUDIOSTANDARD_DK_NICAM_,
	EN_AUDIOSTANDARD_L_,
	EN_AUDIOSTANDARD_LP_,
	EN_AUDIOSTANDARD_M_,
	EN_AUDIOSTANDARD_M_BTSC_,
	EN_AUDIOSTANDARD_M_A2_,
	EN_AUDIOSTANDARD_M_EIA_J_,
	EN_AUDIOSTANDARD_NOTSTANDARD_,
	EN_AUDIOSTANDARD_AUTO_,
    EN_AUDIOSTANDARD_MAX
};

/**
 * @brief Types of color systems
 */
enum fpp_color_system {
	EN_VIDEOSTANDARD_PAL_BGHI,
	EN_VIDEOSTANDARD_NTSC_M,
	EN_VIDEOSTANDARD_SECAM,
	EN_VIDEOSTANDARD_NTSC_44,
	EN_VIDEOSTANDARD_PAL_M,
	EN_VIDEOSTANDARD_PAL_N,
	EN_VIDEOSTANDARD_PAL_60,
    EN_VIDEOSTANDARD_NOTSTANDARD,
	EN_VIDEOSTANDARD_AUTO,
	EN_VIDEOSTANDARD_MAX
};

/**
 * fpp_signal_check_routine is not documented yet.
 * unused
 */
//void fpp_signal_check_routine(void);

/**
 * @brief Get the current color space
 * @param linein linein to get the color space from
 * @param reserved unknown (maybe signal id), alaway set to 0
 * @param color_space pointer to an uin8_t to the color space to
 */
void fpp_signal_get_color_space(uint32_t linein, uint8_t reserved, uint8_t *color_space);

/**
 * @brief get the color system
 * @param linein the linein to get color system from
 * @param system where to write the color system to
 */
void fpp_signal_get_color_system(uint32_t linein, enum fpp_color_system *system);

/**
 * @brief Get the displayed framerate
 * @param framerate where to write the framerate to
 */
void fpp_signal_get_disp_framerate(uint8_t *framerate);

/**
 * @brief Get the video signal format
 * @param linein the linein to get the format from
 * @param id where to write the format id to
 * @param format where to write the format details to
 */
void fpp_signal_get_format(uint32_t linein, uint32_t *id, struct fpp_signal_format_short *format);

/**
 * @brief Get the analog frequency of the input signal
 * @param linein the linein to get signal frequency from
 * @param frquency where to write the frequency to
 */
void fpp_signal_get_frequncy(uint32_t linein, uint16_t *frequency);

/**
 * @brief Get the HDMI provider type (PC, Video, apparently)
 * @param provider pointer where to write the provider type to
 */
void fpp_signal_get_hdmi_provider_type(enum fpp_hdmi_provider_type *provider);

/**
 * fpp_signal_get_info is not documented yet.
 * unused, apparently can get info about "film" (film_mode?) and xvycc
 */
//void fpp_signal_get_info(void);

/**
 * fpp_signal_get_lock_state is not documented yet.
 * unused
 */
//void fpp_signal_get_lock_state(void);

/**
 * @brief Get the sound system type
 * @param system where to write the sound system to
 */
void fpp_signal_get_sound_system(enum fpp_sound_system *system);

/**
 * @brief Get the video size
 * @param linein input line to get the video size of
 * @param reserved unknown usage, set to zero
 * @param width where to write the width to
 * @param height where to write the height to
 */
void fpp_signal_get_video_size(uint32_t linein, uint8_t reserved, uint16_t *width, uint16_t *height);

/**
 * fpp_signal_get_wss is not documented yet.
 * unused, is about widescreen signaling, a way to say "i'm 16:9" for old TVs
 */
//void fpp_signal_get_wss(void);

/**
 * fpp_signal_is_dvi is not documented yet.
 * unused, i suppose say if signal is dvi-on-hdmi or "real" hdmi
 */
//void fpp_signal_is_dvi(void);

/**
 * fpp_signal_is_interlaced is not documented yet.
 * unused, should say if the signal is enterlaced
 */
//void fpp_signal_is_interlaced(void);

/**
 * fpp_signal_monitor_afd_change is not documented yet.
 * unused, is about "active format description" an old system for broadcast TV
 */
//void fpp_signal_monitor_afd_change(void);

/**
 * @brief "un-init" a monitor
 * @param linein (optional) linein to "un-init" for
 */
//void fpp_signal_monitor_exinit(uint32_t linein);

/**
 * @brief Monitor for format changes and call the callback if it does change
 * @param linein the linein to trigger for
 * @param enabled enable or disable the trigger
 * @param callback function to call when format changes
 */
void fpp_signal_monitor_formatchange(uint32_t linein, uint8_t enabled, void (*callback)(void));

/**
 * @brief Init the monitor for a given linein
 * @param linein the linein to init the monitor for
 */
void fpp_signal_monitor_init(uint32_t linein);

/**
 * @brief Monitor for signal lock (what is this?) and call the callback if needed
 * @param linein the linein to trigger for
 * @param enabled enable or disable the trigger
 * @param callback function to call when signal is locked (?)
 */
void fpp_signal_monitor_lock(uint32_t linein, uint8_t enabled, void (*callback)(void));

/**
 * fpp_signal_monitor_scart_change is not documented yet.
 * unused, only for scart, who use this thing on a 4k tv?
 */
//void fpp_signal_monitor_scart_change(void);

/**
 * @brief Call the callback if we plugged the given linein
 * @param linein the linein to trigger for
 * @param enabled enable or disable the trigger
 * @param callback function to call when cable is plugged
 */
void fpp_signal_monitor_src_insert(uint32_t linein, uint8_t enabled, void (*callback)(void));

/**
 * @brief Monitor for signal unlock (what is this?) and call the callback if needed
 * @param linein the linein to trigger for
 * @param enabled enable or disable the trigger
 * @param callback function to call when signal is unlocked (?)
 */
void fpp_signal_monitor_unlock(uint32_t linein, uint8_t enabled, void (*callback)(void));

/**
 * fpp_signal_monitor_wss_change is not documented yet.
 * unused, we don't use widescreen signaling
 */
//void fpp_signal_monitor_wss_change(void);

/**
 * @brief force a color standard for the current linein
 * @param reserved unknown usage, always set to 1
 * @system the color system to force
 */
void fpp_signal_set_color_system(uint8_t reserved, enum fpp_color_system system);

/**
 * @brief force a hdmi provider type for the current linein
 * @param type the provider type to force
 */
void fpp_signal_set_hdmi_provider_type(enum fpp_hdmi_provider_type type);

/**
 * @brief force a sound system for the current linein
 * @param reserved unknown, always set to 1
 * @param system the sound system to force
 */
void fpp_signal_set_sound_system(uint8_t reserved, enum fpp_sound_system system);

#endif /* __FPP_SIGNAL_H__ */
