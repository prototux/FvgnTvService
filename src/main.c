#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include <fpp/fpp.h>
#include <onion/onion.h>
#include <onion/dict.h>
#include <onion/block.h>
#include <onion/request.h>
#include <onion/response.h>
#include <onion/url.h>
#include <onion/low.h>

#include "tools.h"
#include "api.h"
#include "platform.h"

int main(int argc, char *argv[])
{
	// Init FPP
	platform_init();
	platform_open_hdmi();
	platform_power_set_led(0);

	// Libonion init
	onion *o = onion_new(O_ONE_LOOP);
	onion_url *url = onion_root_url(o);

	// Audio endpoints
	onion_url_add(url, "audio/mutes", (void*)api_audio_mutes);
	onion_url_add(url, "audio/headphones", (void*)api_audio_headphones);
	onion_url_add(url, "audio/speaker", (void*)api_audio_speaker);
	onion_url_add(url, "audio/volume", (void*)api_audio_volume);
	onion_url_add(url, "audio/mic", (void*)api_audio_mic);

	// Power endpoints
	onion_url_add(url, "power$", api_power);
	onion_url_add(url, "power/panel", api_power_panel);
	onion_url_add(url, "power/led", api_power_led);
	onion_url_add(url, "power/methods", api_power_methods);
	onion_url_add(url, "power/sleep", api_power_sleep);

	// Panel endpoints
	onion_url_add(url, "panel/video_mirror", api_panel_video_mirror);
	onion_url_add(url, "panel/osd_mirror", api_panel_osd_mirror);
	onion_url_add(url, "panel/bit_mode", api_panel_bit_mode);
	onion_url_add(url, "pamel/polarity", api_panel_polarity);
	onion_url_add(url, "panel/swap_port", api_panel_swap_port);
	onion_url_add(url, "panel/ti_mode", api_panel_ti_mode);

	// Input endpoints
	onion_url_add(url, "input$", api_input);
	onion_url_add(url, "input/plugged", api_input_plugged);

	// Video endpoints
	onion_url_add(url, "video/dynamic_contrast", api_video_dynamic_contrast);
	onion_url_add(url, "video/film_mode", api_video_film_mode);
	onion_url_add(url, "video/mute", api_video_mute);
	onion_url_add(url, "video/mute_color", api_video_mute_color);
	onion_url_add(url, "video/backlight", api_video_backlight);
	onion_url_add(url, "video/black_stretch", api_video_black_stretch);
	onion_url_add(url, "video/brightness", api_video_brightness);
	onion_url_add(url, "video/contrast", api_video_contrast);
	onion_url_add(url, "video/flesh_tone", api_video_flesh_tone);
	onion_url_add(url, "video/game_mode", api_video_game_mode);
	onion_url_add(url, "video/gamma", api_video_gamma);
	onion_url_add(url, "video/hue", api_video_hue);
	onion_url_add(url, "video/white_balance", api_video_white_balance);
	onion_url_add(url, "video/noise_reduction", api_video_noise_reduction);
	onion_url_add(url, "video/saturation", api_video_saturation);
	onion_url_add(url, "video/sharpness", api_video_sharpness);

	// Zoom endpoints
	onion_url_add(url, "zoom/crop_window", api_zoom_crop_window);
	onion_url_add(url, "zoom/display_window/", api_zoom_display_window);

	// System endpoints
	onion_url_add(url, "system$", api_system);
	onion_url_add(url, "system/4k2k", api_system_4k2k);
	onion_url_add(url, "system/luma", api_system_luma);
	onion_url_add(url, "system/bluetooth", api_system_bluetooth);
	onion_url_add(url, "system/time", api_system_time);
	onion_url_add(url, "system/notification", api_system_notification);
	onion_url_add(url, "system/osd", api_system_osd);

	// Listen
	onion_listen(o);
	return EXIT_SUCCESS;
}
