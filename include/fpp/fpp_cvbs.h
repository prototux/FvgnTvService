/**
 * @file fpp_cvbs.h
 * fpp_cvbs is not defined yet
 */
#ifndef __FPP_CVBS_H__
#define __FPP_CVBS_H__

#include <inttypes.h>

/**
 * @brief React to format change
 */
void fpp_cvbs_process_signal_formatchange(uint32_t linein, struct fpp_signal_format format);

/**
 * @brief React to signal lock (???)
 */
void fpp_cvbs_process_signal_locked(uint32_t linein, uint32_t signal_id, uint8_t unknown);

/**
 * @brief React to signal unlock (???)
 */
void fpp_cvbs_process_signal_unlock(uint32_t linein);

#endif /* __FPP_CVBS_H__ */
