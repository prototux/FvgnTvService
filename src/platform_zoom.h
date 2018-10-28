#ifndef __PLATFORM_ZOOM_H__
#define __PLATFORM_ZOOM_H__

#include <fpp/fpp.h>

// Current zoom settings
extern uint32_t platform_zoom_current_crop_start_x;
extern uint32_t platform_zoom_current_crop_start_y;
extern uint32_t platform_zoom_current_crop_width;
extern uint32_t platform_zoom_current_crop_height;
extern uint32_t platform_zoom_current_window_pos_x;
extern uint32_t platform_zoom_current_window_pos_y;
extern uint32_t platform_zoom_current_window_width;
extern uint32_t platform_zoom_current_window_height;

// Functions
void platform_window_crop(uint32_t linein, uint32_t start_x, uint32_t start_y, uint32_t width, uint32_t height);
void platform_window_pos(uint32_t linein, uint32_t pos_x, uint32_t pos_y, uint32_t width, uint32_t height);

#endif /* __PLATFORM_ZOOM_H__ */
