#include <stdio.h>
#include <stdlib.h>
#include "cs229.h"

int isBlack(PixelPtr p);
int isWhite(PixelPtr p);

int main(int argc, const char *argv[])
{
	FILE *dataIn;
	float blackCount = 0.0, whiteCount = 0.0;
	int w, h;
	ImagePtr image;

	/* either use stdin or the file */
	if (argc == 2) {
		dataIn = fopen(argv[1], "r");
		if (dataIn == NULL) {
			fprintf(stderr, "unable to read image\n");
			return 1;
		}
	} else {
		dataIn = stdin;
	}

	image = readImage(dataIn);
	if (image == NULL) {
		fprintf(stderr, "invalid image\n");
		return 1;
	}

	/* go through the pixels and determine their values */
	for(h = 0; h < image->height; h++) {
		for(w = 0; w < image->width; w++) {
			blackCount += isBlack(&image->data[h][w]);
			whiteCount += isWhite(&image->data[h][w]);
		}
	}
	
	/* print the statistics */
	printf("%s\n", (image->bwOrC == 255) ? "Color" : "Black and White");
	printf("Channels: %i, %i, %i\n", image->rChannel, image->gChannel, image->bChannel);
	printf("%i x %i = %i pixels\n", image->width, image->height, image->width * image->height);
	printf("%.2f%% White\n", whiteCount / (image->height * image->width) * 100.0);
	printf("%.2f%% Black\n", blackCount / (image->height * image->width) * 100.0);
	
	return 0;
}

int isWhite(PixelPtr p) {
	return (p->r == 65535 && p->g == 65535 && p->b == 65535);
}

int isBlack(PixelPtr p) {
	return (p->r == 0 && p->g == 0 && p->b == 0);
}
