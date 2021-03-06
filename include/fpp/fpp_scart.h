/**
 * @file fpp_scart.h
 * fpp_scart is not defined yet
 */
#ifndef __FPP_SCART_H__
#define __FPP_SCART_H__

#include <inttypes.h>

/**
 * fpp_scart_get_pin16_level is not documented yet.
 */
void fpp_scart_get_pin16_level(void);

/**
 * fpp_scart_get_pin8_level is not documented yet.
 */
void fpp_scart_get_pin8_level(void);

/**
 * fpp_scart_get_port_enable_status is not documented yet.
 */
void fpp_scart_get_port_enable_status(void);

/**
 * fpp_scart_init is not documented yet.
 */
void fpp_scart_init(void);

/**
 * fpp_scart_in_set_video_type is not documented yet.
 */
void fpp_scart_in_set_video_type(void);

/**
 * fpp_scart_out_insert_ttx is not documented yet.
 */
void fpp_scart_out_insert_ttx(void);

/**
 * fpp_scart_out_mute is not documented yet.
 */
void fpp_scart_out_mute(void);

/**
 * fpp_scart_out_set_cgms_a_mode is not documented yet.
 */
void fpp_scart_out_set_cgms_a_mode(void);

/**
 * fpp_scart_out_set_macrovision_mode is not documented yet.
 */
void fpp_scart_out_set_macrovision_mode(void);

/**
 * fpp_scart_out_set_pin8_level is not documented yet.
 */
void fpp_scart_out_set_pin8_level(void);

/**
 * fpp_scart_out_set_source is not documented yet.
 */
void fpp_scart_out_set_source(void);

/**
 * fpp_scart_out_set_video_type is not documented yet.
 */
void fpp_scart_out_set_video_type(void);

/**
 * fpp_scart_out_set_wss is not documented yet.
 */
void fpp_scart_out_set_wss(void);

/**
 * @brief React to format change
 */
void fpp_scart_process_signal_formatchange(uint32_t linein, struct fpp_signal_format format);

/**
 * @brief React to signal lock (???)
 */
void fpp_scart_process_signal_locked(uint32_t linein, uint32_t signal_id, uint8_t unknown);

/**
 * @brief React to signal unlock (???)
 */
void fpp_scart_process_signal_unlock(uint32_t linein);

#endif /* __FPP_SCART_H__ */
