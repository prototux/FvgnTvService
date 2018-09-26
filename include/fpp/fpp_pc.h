/**
 * @file fpp_pc.h
 * fpp_pc is not defined yet
 */
#ifndef __FPP_PC_H__
#define __FPP_PC_H__

/**
 * @brief React to format change
 */
void fpp_pc_process_signal_formatchange(uint32_t linein, struct fpp_signal_format format);

/**
 * @brief React to signal lock (???)
 */
void fpp_pc_process_signal_locked(uint32_t linein, uint32_t signal_id, uint8_t unknown);

/**
 * @brief React to signal unlock (???)
 */
void fpp_pc_process_signal_unlock(uint32_t linein);

#endif /* __FPP_PC_H__ */
