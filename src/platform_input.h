#ifndef __PLATFORM_INPUT_H__
#define __PLATFORM_INPUT_H__

#include <fpp/fpp.h>

// Input definitions
#define PLATFORM_INPUTS_COUNT 18
struct platform_input_def {
    char *name;
    uint32_t id;
	uint8_t analog;
};

extern uint32_t platform_input_current_linein;
extern struct platform_input_def platform_inputs[];

uint32_t platform_input_get_id_from_name(char *name);
char *platform_input_get_name_from_id(uint32_t id);
uint8_t platform_input_formatchange(void);
uint8_t platform_input_switch_to(uint32_t input);
void platform_input_get_video_size(uint32_t linein, uint16_t *width, uint16_t *height);
uint16_t platform_input_get_framerate(uint32_t linein);
uint16_t platform_input_get_analog_frequency(uint32_t linein);
uint32_t platform_input_get_color_space(uint32_t linein);
uint8_t platform_input_get_status(uint32_t linein);
uint8_t platform_input_get_lock_state(uint32_t linein);
uint8_t platform_input_is_interlaced(uint32_t linein);
uint8_t platform_input_is_dvi(uint32_t linein);
void platform_input_get_vga_infos(uint16_t *hpos, uint16_t *vpos, uint16_t *clock, uint16_t *phase);
void platform_input_get_format(uint32_t linein, struct fpp_signal_format *format);
uint8_t platform_input_plugged(void);
uint8_t platform_input_plugged(void);
uint8_t platform_input_locked(void);
uint8_t platform_input_unlock(void);

#endif /* __PLATFORM_INPUT_H__ */
