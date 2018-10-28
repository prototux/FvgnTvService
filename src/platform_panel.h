#ifndef __PLATFORM_PANEL_H__
#define __PLATFORM_PANEL_H__

#include <fpp/fpp.h>

// Current panel settings
extern uint8_t platform_panel_current_video_mirror;
extern uint8_t platform_panel_current_osd_mirror;

// Functions
void platform_panel_get_resolution(uint16_t *width, uint16_t *height);
uint8_t platform_panel_get_average_luma();
uint8_t platform_panel_get_luma_distribution(uint16_t *results);
uint8_t platform_panel_set_video_mirror(uint8_t enabled);
uint8_t platform_panel_set_osd_mirror(uint8_t enabled);

#endif /* __PLATFORM_PANEL_H__ */
