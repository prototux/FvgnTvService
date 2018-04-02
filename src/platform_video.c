#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <fpp/fpp.h>

struct fpp_video_adj int2adj(int val)
{
	struct fpp_video_adj item = {
		.value = val,
		.min = val,
		.low = val,
		.mid = val,
		.high = val,
		.max = val
	};
	return item;
}

int platform_video_set_brightness(int brightness)
{
	struct fpp_video_adj brightness_adj = int2adj(brightness);
	fpp_video_set_brightness(1, &brightness_adj);
	return 1;
}
