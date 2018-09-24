#ifndef __PLATFORM_INPUT_H__
#define __PLATFORM_INPUT_H__

extern uint32_t platform_input_current_linein;

uint8_t platform_input_formatchange(void);
uint8_t platform_input_switch_to(uint32_t input);
void platform_input_get_video_size(uint32_t linein, uint16_t *width, uint16_t *height);
uint16_t platform_input_get_framerate(uint32_t linein);
uint16_t platform_input_get_analog_frequency(uint32_t linein);
uint32_t platform_input_get_color_space(uint32_t linein);
uint8_t platform_input_get_status(uint32_t linein);

#endif /* __PLATFORM_INPUT_H__ */
