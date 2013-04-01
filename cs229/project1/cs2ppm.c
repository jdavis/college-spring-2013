#include <stdio.h>
#include "cs229.h"

int main(int argc, const char *argv[])
{
	int w, h, channel, max;
	ImagePtr image = readImage(stdin);
	PixelPtr p;

	if (image == NULL) {
		return 1;
	}

	if ((image->rChannel != 8 && image->rChannel != 16) || image->bwOrC != 255) {
		fprintf(stderr, "channels not correct or not a color image\n");
		return 1;
	} else if (image->rChannel != image->gChannel || image->gChannel != image->bChannel) {
		fprintf(stderr, "channels not the same");
		return 1;
	}

	channel = image->rChannel;
	max = pow2(channel) - 1;
	printf("%s\n%i\n%i\n%i\n", "P6", image->width, image->height, max);

	for(h = 0; h < image->height; h++) {
		for(w = 0; w < image->width; w++) {
			p = &(image->data[h][w]);
			writePixel(stdout, p, channel, channel, channel, (char) 255);
		}
	}

	return 0;
}
