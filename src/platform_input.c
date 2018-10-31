#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <fpp/fpp.h>
#include "platform.h"

uint32_t platform_input_current_linein = 0;
struct platform_input_def platform_inputs[] = {
    { "hdmi-1", LINEIN_HDMI1, 0, 0 },
    { "hdmi-2", LINEIN_HDMI2, 0, 0 },
    { "hdmi-3", LINEIN_HDMI3, 0, 0 },
    { "hdmi-4", LINEIN_HDMI4, 0, 0 },
    { "composite-1", LINEIN_CVBS1, 1, 0 },
    { "composite-2", LINEIN_CVBS2, 1, 0 },
    { "composite-3", LINEIN_CVBS3, 1, 0 },
    { "composite-4", LINEIN_CVBS4, 1, 0 },
    { "svideo-1", LINEIN_SVIDEO1, 1, 0 },
    { "svideo-2", LINEIN_SVIDEO2, 1, 0 },
    { "component-1", LINEIN_COMPONENT1, 1, 0 },
    { "component-2", LINEIN_COMPONENT2, 1, 0 },
    { "component-3", LINEIN_COMPONENT3, 1, 0 },
    { "component-4", LINEIN_COMPONENT4, 1, 0 },
    { "vga-1", LINEIN_PC1, 1, 0 },
    { "vga-2", LINEIN_PC2, 1, 0 },
    { "scart-1", LINEIN_SCART1, 1, 0 },
    { "scart-2", LINEIN_SCART2, 1, 0 }
};


uint32_t platform_input_get_id_from_name(char *name)
{
	for (int i = 0; i < PLATFORM_INPUTS_COUNT; i++)
		if (!strcmp(platform_inputs[i].name, name))
			return platform_inputs[i].id;
	return 0;
}

char *platform_input_get_name_from_id(uint32_t id)
{
	for (int i = 0; i < PLATFORM_INPUTS_COUNT; i++)
		if (platform_inputs[i].id == id)
			return platform_inputs[i].name;
	return (char*)NULL;
}

void platform_input_enable(const char *name)
{
	for (int i = 0; i < PLATFORM_INPUTS_COUNT; i++)
		if (!strcmp(platform_inputs[i].name, name))
			platform_inputs[i].enabled = 1;
}

uint8_t platform_input_is_enabled(uint32_t id)
{
	for (int i = 0; i < PLATFORM_INPUTS_COUNT; i++)
		if (platform_inputs[i].id == id)
			return platform_inputs[i].enabled;
	return 0;
}

uint8_t platform_input_unlock(void)
{
	switch (platform_input_current_linein)
	{
		// HDMI Inputs
		case LINEIN_HDMI1:
		case LINEIN_HDMI2:
		case LINEIN_HDMI3:
		case LINEIN_HDMI4:
			fpp_hdmi_process_signal_unlock(platform_input_current_linein);
			break;

		// Composite & S-Video inputs
		case LINEIN_CVBS1:
		case LINEIN_CVBS2:
		case LINEIN_CVBS3:
		case LINEIN_CVBS4:
		case LINEIN_SVIDEO1:
		case LINEIN_SVIDEO2:
			fpp_cvbs_process_signal_unlock(platform_input_current_linein);
			break;

		// Component inputs
		case LINEIN_COMPONENT1:
		case LINEIN_COMPONENT2:
		case LINEIN_COMPONENT3:
		case LINEIN_COMPONENT4:
			fpp_component_process_signal_unlock(platform_input_current_linein);
			break;

		// VGA Inputs
		case LINEIN_PC1:
		case LINEIN_PC2:
			fpp_pc_process_signal_unlock(platform_input_current_linein);
			break;

		// Scart/Peritel inputs
		case LINEIN_SCART1:
		case LINEIN_SCART2:
			fpp_scart_process_signal_unlock(platform_input_current_linein);
			break;

		// Other inputs (CATV, TATV, CDTV, TDTV, Storage)
		// We don't support these so...
		default:
			printf("WARN: Cannot process input %u: unsupported\n", platform_input_current_linein);
	}
	return 0;

}

uint8_t platform_input_locked(void)
{
	struct fpp_signal_format_short format;
	uint32_t id;
	fpp_signal_get_format(platform_input_current_linein, &id, &format);

	switch (platform_input_current_linein)
	{
		// HDMI Inputs
		case LINEIN_HDMI1:
		case LINEIN_HDMI2:
		case LINEIN_HDMI3:
		case LINEIN_HDMI4:
			fpp_hdmi_process_signal_locked(platform_input_current_linein, id, 0);
			break;

		// Composite & S-Video inputs
		case LINEIN_CVBS1:
		case LINEIN_CVBS2:
		case LINEIN_CVBS3:
		case LINEIN_CVBS4:
		case LINEIN_SVIDEO1:
		case LINEIN_SVIDEO2:
			fpp_cvbs_process_signal_locked(platform_input_current_linein, id, 0);
			break;

		// Component inputs
		case LINEIN_COMPONENT1:
		case LINEIN_COMPONENT2:
		case LINEIN_COMPONENT3:
		case LINEIN_COMPONENT4:
			fpp_component_process_signal_locked(platform_input_current_linein, id, 0);
			break;

		// VGA Inputs
		case LINEIN_PC1:
		case LINEIN_PC2:
			fpp_pc_process_signal_locked(platform_input_current_linein, id, 0);
			break;

		// Scart/Peritel inputs
		case LINEIN_SCART1:
		case LINEIN_SCART2:
			fpp_scart_process_signal_locked(platform_input_current_linein, id, 0);
			break;

		// Other inputs (CATV, TATV, CDTV, TDTV, Storage)
		// We don't support these so...
		default:
			printf("WARN: Cannot process input %u: unsupported\n", platform_input_current_linein);
	}
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

	switch (platform_input_current_linein)
	{
		// HDMI Inputs
		case LINEIN_HDMI1:
		case LINEIN_HDMI2:
		case LINEIN_HDMI3:
		case LINEIN_HDMI4:
			fpp_hdmi_process_signal_formatchange(platform_input_current_linein, new_format);
			break;

		// Composite & S-Video inputs
		case LINEIN_CVBS1:
		case LINEIN_CVBS2:
		case LINEIN_CVBS3:
		case LINEIN_CVBS4:
		case LINEIN_SVIDEO1:
		case LINEIN_SVIDEO2:
			fpp_cvbs_process_signal_formatchange(platform_input_current_linein, new_format);
			break;

		// Component inputs
		case LINEIN_COMPONENT1:
		case LINEIN_COMPONENT2:
		case LINEIN_COMPONENT3:
		case LINEIN_COMPONENT4:
			fpp_component_process_signal_formatchange(platform_input_current_linein, new_format);
			break;

		// VGA Inputs
		case LINEIN_PC1:
		case LINEIN_PC2:
			fpp_zoom_vga_autoadjust();
			fpp_pc_process_signal_formatchange(platform_input_current_linein, new_format);
			break;

		// Scart/Peritel inputs
		case LINEIN_SCART1:
		case LINEIN_SCART2:
			fpp_scart_process_signal_formatchange(platform_input_current_linein, new_format);
			break;

		// Other inputs (CATV, TATV, CDTV, TDTV, Storage)
		// We don't support these so...
		default:
			printf("WARN: Cannot process input %u: unsupported\n", platform_input_current_linein);
	}
	fpp_zoom_set_crop_window(platform_input_current_linein, &new_format, 0, 0, new_format.width, new_format.height);
	fpp_zoom_set_display_window(platform_input_current_linein, &new_format, 0, 0, 1920, 1080);
	fpp_zoom_set_aspect_ratio(0);
	usleep(100000);
	platform_video_mute(0);
	return 0;
}

uint8_t platform_input_plugged(void)
{
	printf("Current input (%x) got plugged!\n", platform_input_current_linein);
	if (platform_input_current_linein == LINEIN_PC1 || platform_input_current_linein == LINEIN_PC2)
		fpp_zoom_vga_autoadjust();
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

	if (!platform_input_get_status(input))
	{
		printf("ERROR: Input not plugged\n");
		return 3;
	}

	// Some log...
	printf("INFO: Switching linein from %x to %x\n", platform_input_current_linein, input);

	// Mute video to avoid visible artifacts
	platform_video_mute(1);

	// Avoid crashing if first selection
	if (platform_input_current_linein)
	{
		printf("Closing current linein %d\n", platform_input_current_linein);

		// Disable the monitors
		fpp_signal_monitor_unlock(platform_input_current_linein, 0, 0);
		fpp_signal_monitor_lock(platform_input_current_linein, 0, 0);
		fpp_signal_monitor_formatchange(platform_input_current_linein, 0, 0);
		fpp_signal_monitor_src_insert(platform_input_current_linein, 0, 0);
		fpp_signal_monitor_exinit(platform_input_current_linein);

		// Close the current linein
		switch (platform_input_current_linein)
		{
			// HDMI Inputs
			case LINEIN_HDMI1:
			case LINEIN_HDMI2:
			case LINEIN_HDMI3:
			case LINEIN_HDMI4:
				fpp_linein_close_hdmi(platform_input_current_linein);
				break;

			// Composite & S-Video inputs
			case LINEIN_CVBS1:
			case LINEIN_CVBS2:
			case LINEIN_CVBS3:
			case LINEIN_CVBS4:
			case LINEIN_SVIDEO1:
			case LINEIN_SVIDEO2:
				fpp_linein_close_cvbs(platform_input_current_linein);
				break;

			// Component inputs
			case LINEIN_COMPONENT1:
			case LINEIN_COMPONENT2:
			case LINEIN_COMPONENT3:
			case LINEIN_COMPONENT4:
				fpp_linein_close_component(platform_input_current_linein);
				break;

			// VGA Inputs
			case LINEIN_PC1:
			case LINEIN_PC2:
				fpp_linein_close_pc(platform_input_current_linein);
				break;

			// Scart/Peritel inputs
			case LINEIN_SCART1:
			case LINEIN_SCART2:
				fpp_linein_close_scart(platform_input_current_linein);
				break;

			// Other inputs (CATV, TATV, CDTV, TDTV, Storage)
			// Don't close them as they should have never been open in the first place
			default:
				printf("WARN: Cannot close input %u: unsupported\n", platform_input_current_linein);
		}
	}
	else
		printf("Skipped closing for linein %d\n", platform_input_current_linein);

	platform_video_freeze(0);

	platform_input_current_linein = input;

	// Start monitors for new linein
	fpp_signal_monitor_exinit(platform_input_current_linein);
	fpp_signal_monitor_init(input);
	fpp_signal_monitor_formatchange(platform_input_current_linein, 1, platform_input_formatchange);
	fpp_signal_monitor_src_insert(platform_input_current_linein, 1, platform_input_plugged);
	// Lock just blackout the screen now
	fpp_signal_monitor_unlock(input, 1, platform_input_unlock);
	//fpp_signal_monitor_lock(input, 1, platform_input_locked);

	// Open the new linein
	switch (platform_input_current_linein)
	{
		// HDMI Inputs
		case LINEIN_HDMI1:
		case LINEIN_HDMI2:
		case LINEIN_HDMI3:
		case LINEIN_HDMI4:
			fpp_linein_open_hdmi(platform_input_current_linein);
			break;

		// Composite & S-Video inputs
		case LINEIN_CVBS1:
		case LINEIN_CVBS2:
		case LINEIN_CVBS3:
		case LINEIN_CVBS4:
		case LINEIN_SVIDEO1:
		case LINEIN_SVIDEO2:
			fpp_linein_open_cvbs(platform_input_current_linein);
			break;

		// Component inputs
		case LINEIN_COMPONENT1:
		case LINEIN_COMPONENT2:
		case LINEIN_COMPONENT3:
		case LINEIN_COMPONENT4:
			fpp_linein_open_component(platform_input_current_linein);
			break;

		// VGA Inputs
		case LINEIN_PC1:
		case LINEIN_PC2:
			fpp_linein_open_pc(platform_input_current_linein);
			break;

		// Scart/Peritel inputs
		case LINEIN_SCART1:
		case LINEIN_SCART2:
			fpp_linein_open_scart(platform_input_current_linein);
			break;

		// Other inputs (CATV, TATV, CDTV, TDTV, Storage)
		// Never open them as storage & TV isn't supported
		default:
			printf("WARN: Cannot open input %u: unsupported\n", platform_input_current_linein);
	}
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
	return 0;
}

void platform_input_get_format(uint32_t linein, struct fpp_signal_format *format)
{
	struct fpp_signal_format_short short_format;
	uint32_t id;
	fpp_signal_get_format(linein, &id, &short_format);
	format->format_id = id;
	format->width = short_format.width;
	format->height = short_format.height;
	format->color_space = platform_input_get_color_space(linein);
	format->dvi = 0;
	format->framerate = short_format.framerate;
	format->interlaced = short_format.interlaced;
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
	uint16_t frequency = 0;
	fpp_signal_get_frequncy(linein, &frequency);
	return frequency;
}

void platform_input_get_vga_infos(uint16_t *hpos, uint16_t *vpos, uint16_t *clock, uint16_t *phase)
{
	fpp_zoom_get_vga_para(hpos, vpos, clock, phase);
}

uint32_t platform_input_get_color_space(uint32_t linein)
{
	uint8_t color_space = 0;
	fpp_signal_get_color_space(linein, 0, &color_space);
	return color_space;
}

uint8_t platform_input_get_status(uint32_t linein)
{
	uint8_t status = 0;
	fpp_linein_src_insert_check(linein, &status);
	printf("Status: %d\n", status);
	return status;
}

uint8_t platform_input_get_lock_state(uint32_t linein)
{
	uint8_t status;
	fpp_signal_get_lock_state(linein, &status);
	return status;
}

uint8_t platform_input_is_interlaced(uint32_t linein)
{
	uint8_t status;
	fpp_signal_is_interlaced(linein, &status);
	return status;
}

uint8_t platform_input_is_dvi(uint32_t linein)
{
    uint8_t status;
    fpp_signal_is_dvi(linein, &status);
    return status;
}

