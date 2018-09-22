/**
 * @file fpp_factory.h
 * fpp_factory is not defined yet
 */
#ifndef __FPP_FACTORY_H__
#define __FPP_FACTORY_H__

enum fpp_watchdog_operation {
	WATCHDOG_ENABLE, /**< Enable the watchdog */
	WATCHDOG_DISABLE, /**< Disable the watchdog */
	WATCHDOG_RESET /**< Reset the watchdog counter */
};

struct fpp_factory_wb {
	uint16_t r_gain; /**< Red gain */
	uint16_t g_gain; /**< Green gain */
	uint16_t b_gain; /**< Blue gain */
	uint16_t r_offset; /**< Red offset */
	uint16_t g_offset; /**< Green offset */
	uint16_t b_offset; /**< Blue offset */
};

/**
 * fpp_factory_close_mode_uart is not documented yet.
 */
void fpp_factory_close_mode_uart(void);

/**
 * fpp_factory_get_ic_version is not documented yet.
 */
void fpp_factory_get_ic_version(void);

/**
 * fpp_factory_ic_dump is not documented yet.
 */
void fpp_factory_ic_dump(void);

/**
 * fpp_factory_ic_write is not documented yet.
 */
void fpp_factory_ic_write(void);

/**
 * fpp_factory_open_mode_uart is not documented yet.
 */
void fpp_factory_open_mode_uart(void);

/**
 * fpp_factory_read_mode_uart is not documented yet.
 */
void fpp_factory_read_mode_uart(void);

/**
 * fpp_factory_set_adc_gain_offset is not documented yet.
 */
void fpp_factory_set_adc_gain_offset(void);

/**
 * fpp_factory_set_auto_adc is not documented yet.
 */
void fpp_factory_set_auto_adc(void);

/**
 * fpp_factory_set_ssc is not documented yet.
 */
void fpp_factory_set_ssc(void);

/**
 * @brief Set white balance (should be in fpp_video?)
 * @param params Parameters structure
 */
int fpp_factory_set_white_balance(struct fpp_factory_wb *params);

/**
 * fpp_factory_uart_operate is not documented yet.
 */
void fpp_factory_uart_operate(void);

/**
 * @brief Operate the watchdog
 * @param op The operation to do
 */
void fpp_factory_watch_dog_operate(enum fpp_watchdog_operation op);

/**
 * fpp_factory_write_mode_uart is not documented yet.
 */
void fpp_factory_write_mode_uart(void);

#endif /* __FPP_FACTORY_H__ */
