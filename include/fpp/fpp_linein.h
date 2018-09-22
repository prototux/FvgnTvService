/**
 * @file fpp_linein.h
 * fpp_linein is not defined yet
 */
#ifndef __FPP_LINEIN_H__
#define __FPP_LINEIN_H__

#include <inttypes.h>

// Inputs
#define LINEIN_CATV 0x00
#define LINEIN_TATV 0x02
#define LINEIN_CDTV 0x04
#define LINEIN_TDTV 0x08
#define LINEIN_CVBS1 0x10
#define LINEIN_CVBS2 0x20
#define LINEIN_CVBS3 0x40
#define LINEIN_CVBS4 0x80
#define LINEIN_SVIDEO1 0x100
#define LINEIN_SVIDEO2 0x200
#define LINEIN_COMPONENT1 0x1000
#define LINEIN_COMPONENT2 0x2000
#define LINEIN_COMPONENT3 0x4000
#define LINEIN_COMPONENT4 0x8000
#define LINEIN_PC1 0x10000
#define LINEIN_PC2 0x20000
#define LINEIN_HDMI1 0x100000
#define LINEIN_HDMI2 0x200000
#define LINEIN_HDMI3 0x400000
#define LINEIN_HDMI4 0x800000
#define LINEIN_SCART1 0x1000000
#define LINEIN_SCART2 0x2000000
#define LINEIN_STORAGE 0x4000000


/* Doesn't seems to work, the defined values
 * seems to be the correct one
 * #define LINEIN_ID(n) 1<<n

enum fpp_linein {
	LINEIN_CATV = LINEIN_ID(0),
	LINEIN_TATV = LINEIN_ID(1),
	LINEIN_CDTV = LINEIN_ID(2),
	LINEIN_TDTV = LINEIN_ID(3),
	LINEIN_CVBS1 = LINEIN_ID(4),
	LINEIN_CVBS2 = LINEIN_ID(5),
	LINEIN_CVBS3 = LINEIN_ID(6),
	LINEIN_CVBS4 = LINEIN_ID(7),
	LINEIN_SVIDEO1 = LINEIN_ID(8),
	LINEIN_SVIDEO2 = LINEIN_ID(9),
	LINEIN_COMPONENT1 = LINEIN_ID(10),
	LINEIN_COMPONENT2 = LINEIN_ID(11),
	LINEIN_COMPONENT3 = LINEIN_ID(12),
	LINEIN_COMPONENT4 = LINEIN_ID(13),
	LINEIN_PC1 = LINEIN_ID(14),
	LINEIN_PC2 = LINEIN_ID(15),
	LINEIN_HDMI1 = LINEIN_ID(16),
	LINEIN_HDMI2 = LINEIN_ID(17),
	LINEIN_HDMI3 = LINEIN_ID(18),
	LINEIN_HDMI4 = LINEIN_ID(19),
	LINEIN_SCART1 = LINEIN_ID(20),
	LINEIN_SCART2 = LINEIN_ID(21),
	LINEIN_STORAGE = LINEIN_ID(22)
};*/

/**
 * fpp_linein_atv_play is not documented yet.
 */
void fpp_linein_atv_play(void);

/**
 * fpp_linein_atv_stop is not documented yet.
 */
void fpp_linein_atv_stop(void);

/**
 * fpp_linein_close_atv is not documented yet.
 */
void fpp_linein_close_atv(void);

/**
 * fpp_linein_close_component is not documented yet.
 */
void fpp_linein_close_component(void);

/**
 * fpp_linein_close_cvbs is not documented yet.
 */
void fpp_linein_close_cvbs(void);

/**
 * fpp_linein_close_dtv is not documented yet.
 */
void fpp_linein_close_dtv(void);

/**
 * fpp_linein_close_hdmi is not documented yet.
 */
void fpp_linein_close_hdmi(void);

/**
 * fpp_linein_close_ktv is not documented yet.
 */
void fpp_linein_close_ktv(void);

/**
 * fpp_linein_close_pc is not documented yet.
 */
void fpp_linein_close_pc(void);

/**
 * fpp_linein_close_scart is not documented yet.
 */
void fpp_linein_close_scart(void);

/**
 * fpp_linein_close_storage is not documented yet.
 */
void fpp_linein_close_storage(void);

/**
 * fpp_linein_close_svideo is not documented yet.
 */
void fpp_linein_close_svideo(void);

/**
 * fpp_linein_open_atv is not documented yet.
 */
void fpp_linein_open_atv(void);

/**
 * fpp_linein_open_component is not documented yet.
 */
void fpp_linein_open_component(void);

/**
 * fpp_linein_open_cvbs is not documented yet.
 */
void fpp_linein_open_cvbs(void);

/**
 * fpp_linein_open_dtv is not documented yet.
 */
void fpp_linein_open_dtv(void);

/**
 * @brief Opens an HDMI port
 * @param linein The port to open
 */
void fpp_linein_open_hdmi(uint32_t linein);

/**
 * fpp_linein_open_ktv is not documented yet.
 */
void fpp_linein_open_ktv(void);

/**
 * fpp_linein_open_pc is not documented yet.
 */
void fpp_linein_open_pc(void);

/**
 * fpp_linein_open_scart is not documented yet.
 */
void fpp_linein_open_scart(void);

/**
 * fpp_linein_open_storage is not documented yet.
 */
void fpp_linein_open_storage(void);

/**
 * fpp_linein_open_svideo is not documented yet.
 */
void fpp_linein_open_svideo(void);

/**
 * fpp_linein_src_insert_check is not documented yet.
 */
//void fpp_linein_src_insert_check(void);

#endif /* __FPP_LINEIN_H__ */
