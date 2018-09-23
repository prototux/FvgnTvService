#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <fpp/fpp.h>

uint8_t platform_input_current_linein = 0;
uint32_t platform_input_get_color_space(uint32_t linein);

// Not implemented yet
uint8_t platform_input_get_current()
{
	return 0;
}

uint8_t platform_input_formatchange(void)
{
	platform_video_mute(1);

	// Platform?
	uint32_t new_id;
	struct fpp_signal_format_short new_format_short;
	fpp_signal_get_format(platform_input_current_linein, &new_id, &new_format_short);

	// Set new format
	struct fpp_signal_format new_format = {
		.format_id = new_id,
		.width = new_format_short.width,
		.height = new_format_short.height,
		.color_space = platform_input_get_color_space(platform_input_current_linein),
		.dvi = 0,
		.framerate = new_format_short.framerate,
		.interlaced = new_format_short.interlaced
	};
	fpp_hdmi_process_signal_formatchange(platform_input_current_linein, new_format);
	fpp_zoom_set_crop_window(platform_input_current_linein, &new_format, 0, 0, new_format.width, new_format.height);
	fpp_zoom_set_display_window(platform_input_current_linein, &new_format, 0, 0, 1920, 1080);
	usleep(100000);
	platform_video_mute(0);
	return 0;
}

// Highly experimental!
uint8_t platform_input_switch_to(uint32_t input)
{
	if (input == 0)
	{
		printf("ERROR: New linein is incorrect (%x)\n", input);
		return 1;
	}

	if (input == platform_input_current_linein)
	{
		printf("WARN: Same linein\n");
		return 2;
	}

	// Some log...
	printf("INFO: Switching linein from %x to %x\n", platform_input_current_linein, input);

	// TODO: check if new linein is plugged

	// Mute video to avoid visible artifacts
	platform_video_mute(1);

	// Avoid crashing if first selection
	if (platform_input_current_linein)
	{
		// Disable the monitors
		//fpp_signal_monitor_unlock(platform_input_current_linein, 0, 0);
		//fpp_signal_monitor_lock(platform_input_current_linein, 0, 0);
		fpp_signal_monitor_formatchange(platform_input_current_linein, 0, 0);
		// Skiped scart_change, wss_change, afd_change
		fpp_signal_monitor_exinit(platform_input_current_linein);

		// Close the current linein
		if (platform_input_current_linein == LINEIN_HDMI1 || platform_input_current_linein == LINEIN_HDMI2 || platform_input_current_linein == LINEIN_HDMI3 || platform_input_current_linein == LINEIN_HDMI4)
			fpp_linein_close_hdmi(platform_input_current_linein);
		// others not supported yet (*tv, cvbs, svideo, component, pc, scart, storage
	}

	platform_video_freeze(0);

	platform_input_current_linein = input;

	// Start monitors for new linein
	fpp_signal_monitor_exinit();
	fpp_signal_monitor_init(input);
	fpp_signal_monitor_formatchange(input, 1, platform_input_formatchange);
	// Not implemented yet
	//fpp_signal_monitor_unlock(input, 1, ...);
	//fpp_signal_monitor_lock(input, 1, ...);

	if (input == LINEIN_HDMI1 || input == LINEIN_HDMI2 || input == LINEIN_HDMI3 || input == LINEIN_HDMI4)
		fpp_linein_open_hdmi(input);

    // Platform?
    uint32_t new_id;
    struct fpp_signal_format_short new_format_short;
    fpp_signal_get_format(input, &new_id, &new_format_short);

    // Set new format
    struct fpp_signal_format new_format = {
		.format_id = new_id,
 		.width = new_format_short.width,
		.height = new_format_short.height,
		.color_space = platform_input_get_color_space(input),
		.dvi = 0,
 		.framerate = new_format_short.framerate,
 		.interlaced = new_format_short.interlaced
    };
    fpp_hdmi_process_signal_formatchange(input, new_format);
    fpp_zoom_set_crop_window(input, &new_format, 0, 0, new_format.width, new_format.height);
    fpp_zoom_set_display_window(input, &new_format, 0, 0, 1920, 1080);
}

void platform_input_get_video_size(uint32_t linein, uint16_t *width, uint16_t *height)
{
    fpp_signal_get_video_size(linein, 0, width, height);
}

uint16_t platform_input_get_framerate(uint32_t linein)
{
	struct fpp_signal_format_short format;
	uint32_t id;
	fpp_signal_get_format(linein, &id, &format);
	printf("format: %dx%d*%d\n", format.width, format.height, format.framerate);
	return format.framerate/100;
}

uint16_t platform_input_get_analog_frequency(uint32_t linein)
{
	uint16_t frequency;
	fpp_signal_get_frequncy(linein, &frequency);
	return frequency;
}

uint32_t platform_input_get_color_space(uint32_t linein)
{
	uint32_t color_space;
	fpp_signal_get_color_space(linein, 0, &color_space);
	return color_space;
}


uint8_t platform_input_get_status(uint32_t linein)
{
	uint8_t status;
	fpp_linein_src_insert_check(linein, &status);
	printf("Status: %d\n", status);
	return status;
}
