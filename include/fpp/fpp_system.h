/**
 * @file fpp_system.h
 * fpp_system is not defined yet
 */
#ifndef __FPP_SYSTEM_H__
#define __FPP_SYSTEM_H__

/**
 * @brief W*H Resolution
 */
struct fpp_resolution {
	uint16_t width;
	uint16_t height;
};

/**
 * @brief 4k2k mode
 */
enum fpp_system_4k2k_mode {
	MODE_4K2K,
	MODE_MAX
};

/**
 * @brief SoC mode
 */
enum fpp_system_soc_mode {
	SOC_OUT_MODE_4K2K,
	SOC_OUT_MODE_NORMAL,
	SOC_OUT_MODE_MAX
};

/**
 * fpp_system_debug_key_set is not documented yet.
 */
//void fpp_system_debug_key_set(void);

/**
 * @brief Enter SoC out 4k2k mode
 */
void fpp_system_enter_4k2k_mode(enum fpp_system_4k2k_mode mode);

/**
 * @brief Exit SoC out 4k2k mode
 */
void fpp_system_exit_4k2k_mode(enum fpp_system_4k2k_mode mode);

/**
 * fpp_system_fast_create_file is not documented yet.
 */
//void fpp_system_fast_create_file(void);

/**
 * fpp_system_fast_create_file_get_progress is not documented yet.
 */
//void fpp_system_fast_create_file_get_progress(void);

/**
 * @brief Activate the debug menu
 * @param unknown_1 Unknown parameter
 * @param unknown_2 Unknown parameter
 */
void fpp_system_fpp_debug_switch(int unknown_1, int unknown_2);

/**
 * @brief Get average luma
 * @param luma where to write the luma to
 */
void fpp_system_get_average_luma(uint8_t *luma);

/**
 * @brief Get <size> samples of luma and store them to <results>
 * @param results where to store the samples
 * @size number of samples
 */
void fpp_system_get_luma_level_distribution(uint16_t *results, uint8_t size);

/**
 * @brief Get the panel native resolution
 * @param resolution The resolution structure to write to.
 */
void fpp_system_get_panel_resolution(struct fpp_resolution *resolution);

/**
 * fpp_system_get_pixel_info is not documented yet.
 * get pixel info (r/g/b/other?) given a x/y parameter
 */
//void fpp_system_get_pixel_info(void);

/**
 * fpp_system_get_pq_demo_mode is not documented yet.
 */
//void fpp_system_get_pq_demo_mode(void);

/**
 * @brief Apparently init the system
 * It isn't used by sitatvservice and apparently activates the watchdog. it's better to avoid using it.
 */
void fpp_system_init(void);

/**
 * @brief Get if SoC out is 4k2k or normal
 */
void fpp_system_is_4k2k_mode(enum fpp_system_soc_mode *mode);

/**
 * fpp_system_monitor_bluetooth is not documented yet.
 */
//void fpp_system_monitor_bluetooth(void);

/**
 * fpp_system_panel_get_param_bool is not documented yet.
 * value 0 = local-dimming
 */
//void fpp_system_panel_get_param_bool(uint8_t type, uint8_t *value);

/**
 * fpp_system_panel_reset_tcon is not documented yet.
 */
//void fpp_system_panel_reset_tcon(void);

/**
 * fpp_system_panel_set_bit_mode is not documented yet.
 * enum {E_PANEL_TI_BIT_MODE_6_BIT, E_PANEL_TI_BIT_MODE_8_BIT, E_PANEL_TI_BIT_MODE_10_BIT, E_PANEL_TI_BIT_MODE_MAX}
 */
//void fpp_system_panel_set_bit_mode(void);

/**
 * @brief Mirror (or not) the OSD
 */
void fpp_system_panel_set_osd_mirror(uint8_t enabled);

/**
 * fpp_system_panel_set_param_bool is not documented yet.
 * type 0 = local-dimming
 */
//void fpp_system_panel_set_param_bool(uint8_t type, uint8_t value);

/**
 * fpp_system_panel_set_polarity is not documented yet.
 */
//void fpp_system_panel_set_polarity(uint8_t boolean);

/**
 * fpp_system_panel_set_swap_port is not documented yet.
 */
//void fpp_system_panel_set_swap_port(uint8_t boolean);

/**
 * fpp_system_panel_set_ti_mode is not documented yet.
 *  enum {E_PANEL_TI_MODE_VESA, E_PANEL_TI_MODE_JETTA, E_PANEL_TI_MODE_MAX}
 */
//void fpp_system_panel_set_ti_mode(void);

/**
 * @brief Mirror (or not) the video
 */
void fpp_system_panel_set_video_mirror(uint8_t enabled);

/**
 * fpp_system_pwm_set is not documented yet.
 */
//void fpp_system_pwm_set(void);

/**
 * fpp_system_set_bluetooth_enable is not documented yet.
 */
//void fpp_system_set_bluetooth_enable(void);

/**
 * @brief Set some config elements
 * @param id The ID of the config
 * @param path The path of the config file
 * @param path_len The lenght of the path
 */
void fpp_system_set_config_path_and_name(int id, char *path, int path_len);

/**
 * fpp_system_set_gpu_ddr_ratio is not documented yet.
 */
//void fpp_system_set_gpu_ddr_ratio(int32_t);

/**
 * @brief Set panel file path
 * @param path The panel file path
 */
void fpp_system_set_panel_file_name(char *path);

/**
 * fpp_system_set_pq is not documented yet.
 */
//void fpp_system_set_pq(void);

/**
 * fpp_system_set_pq_demo_mode is not documented yet.
 * enum {E_DEMO_OFF, E_DEMO_CUSTOMER1, E_DEMO_CUSTOMER2,
    E_DEMO_CUSTOMER3, E_DEMO_DEFAULT, E_DEMO_DYNAMICCOMPARE, E_DEMO_ENHANCE,
    E_DEMO_GOLDENEYES, E_DEMO_HIGH_SPEED_MOVEMENT_PROCESSING,
    E_DEMO_LED_BACKLIGHT_CONTROL, E_DEMO_MOVEALONG, E_DEMO_OPTIMIZE,
    E_DEMO_SIDE_BY_SIDE, E_DEMO_SQUAREMOVE,
    E_DEMO_TRUE_COLOR_ANALYSIS_ASCENSION, E_DEMO_WIDE_COLOR_ENHANCE,
    E_DEMO_MAX}
 */
//void fpp_system_set_pq_demo_mode(void);

/**
 * @brief Set the Picture Quality paths
 *
 * Set the Picture Quality database paths
 * @param pq PQ database path
 * @param pq_patch PQ patch database path
 */
void fpp_system_set_pq_dir_path(char *pq, char *pq_patch);

/**
 * fpp_system_usb_format is not documented yet.
 */
//void fpp_system_usb_format(void);

/**
 * fpp_system_usb_get_formatting_progress is not documented yet.
 */
//void fpp_system_usb_get_formatting_progress(void);

#endif /* __FPP_SYSTEM_H__ */
