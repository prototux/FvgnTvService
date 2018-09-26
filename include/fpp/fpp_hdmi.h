/**
 * @file fpp_hdmi.h
 * fpp_hdmi is not defined yet
 */
#ifndef __FPP_HDMI_H__
#define __FPP_HDMI_H__

#include <inttypes.h>

/**
 * @brief React to format change
 */
void fpp_hdmi_process_signal_formatchange(uint32_t linein, struct fpp_signal_format format);

/**
 * @brief React to signal lock (???)
 */
void fpp_hdmi_process_signal_locked(uint32_t linein, uint32_t signal_id, uint8_t unknown);

/**
 * @brief React to signal unlock (???)
 */
void fpp_hdmi_process_signal_unlock(uint32_t linein);

#endif /* __FPP_HDMI_H__ */
