/**
 * @file fpp_zoom.h
 * fpp_zoom is not defined yet
 */
#ifndef __FPP_ZOOM_H__
#define __FPP_ZOOM_H__

#include <inttypes.h>

/**
 * fpp_zoom_get_afd_info is not documented yet.
 */
void fpp_zoom_get_afd_info(void);

/**
 * @brief return the vga paramters
 */
void fpp_zoom_get_vga_para(uint16_t *hpos, uint16_t *vpos, uint16_t *clock, uint16_t *phase);

/**
 * fpp_zoom_set_aspect_ratio is not documented yet.
 * 1 in a specific case (E_AR_PANORAMA), else 0, so... 0
 */
void fpp_zoom_set_aspect_ratio(uint8_t aspect_ratio);

/**
 * @brief Sets the crop parameters of a specific linein
 * @param linein The linein to edit
 * @param format The signal format
 * @param x The X position of the window
 * @param y The Y position of the window
 * @param width The width of the window
 * @param height The height of the window
 */
void fpp_zoom_set_crop_window(uint32_t linein, struct fpp_signal_format *format, int x, int y, int width, int height);

/**
 * @brief Sets the display window parameters of a specific linein
 * @param linein The linein to edit
 * @param format The signal format
 * @param x The X position of the window
 * @param y The Y position of the window
 * @param width The width of the window
 * @param height The height of the window
 */
void fpp_zoom_set_display_window(uint32_t linein, struct fpp_signal_format *format, int x, int y, int width, int height);

/**
 * fpp_zoom_set_vga_clock is not documented yet.
 */
void fpp_zoom_set_vga_clock(void);

/**
 * fpp_zoom_set_vga_hpos is not documented yet.
 */
void fpp_zoom_set_vga_hpos(void);

/**
 * fpp_zoom_set_vga_phase is not documented yet.
 */
void fpp_zoom_set_vga_phase(void);

/**
 * fpp_zoom_set_vga_vpos is not documented yet.
 */
void fpp_zoom_set_vga_vpos(void);

/**
 * fpp_zoom_vga_autoadjust is not documented yet.
 */
void fpp_zoom_vga_autoadjust(void);

#endif /* __FPP_ZOOM_H__ */
