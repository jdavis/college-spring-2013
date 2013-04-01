#include <stdio.h>
#include <string.h>
#include "cs229.h"

int main(int argc, const char *argv[])
{
	int w, h, isHorizontal;
	ImagePtr image;
	PixelPtr p1, p2;

	if (argc != 2) {
		fprintf(stderr, "invalid arguments\nflip (h | v) < image\n");
		return 1;
	}

	/* determine if we should do a horiztonal or vertical flip */
	if (!strcmp("h", argv[1])) {
		isHorizontal = 1;
	} else if (!strcmp("v", argv[1])) {
		isHorizontal = 0;
	} else {
		fprintf(stderr, "invalid option\nflip (h | v) < image\n");
		return 1;
	}

	image = readImage(stdin);

	if (image == NULL) {
		return 1;
	}

	/* just swap the pixels to perform the flip */
	/* the new pixel is determined by the operation and the max width or height */
	if (isHorizontal) {
		for(h = 0; h < image->height; h++) {
			for(w = 0; w < image->width / 2; w++) {
				p1 = &(image->data[h][w]);
				p2 = &(image->data[h][image->width - w - 1]);
				swapPixels(p1, p2);
			}
		}
	} else {
		for(h = 0; h < image->height / 2; h++) {
			for(w = 0; w < image->width; w++) {
				p1 = &(image->data[h][w]);
				p2 = &(image->data[image->height - h - 1][w]);
				swapPixels(p1, p2);
			}
		}
	}

	writeImage(image);
	
	return 0;
}
