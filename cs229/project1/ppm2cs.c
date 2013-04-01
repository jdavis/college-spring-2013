#include "cs229.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 1024

int main(int argc, const char *argv[])
{
	char identifierStr[MAX], widthStr[MAX], heightStr[MAX], maxStr[MAX], channel;
	int width, height, max;
	int w, h;
	ImagePtr image;

	scanf("%s %s %s %s", identifierStr, widthStr, heightStr, maxStr);
	
	/* test and set the values we read from the PPM file */
	if (strcmp(identifierStr, "P6") != 0) {
		fprintf(stderr, "Invalid ppm file\n");
		return 1;
	}

	width = atoi(widthStr);
	height = atoi(heightStr);

	if (width <= 0 || height <= 0) {
		fprintf(stderr, "Invalid ppm file\n");
		return 1;
	}

	/* determine the right channel to use */
	max = atoi(maxStr);
	if (max < 256) {
		channel = 8;
	} else {
		channel = 16;
	}

	/* an empty image to store the read pixels */
	image = emptyImage(height, width);

	image->rChannel = channel;
	image->gChannel = channel;
	image->bChannel = channel;
	image->bwOrC = 255;

	/* get separating whitespace */
	getchar();

	image->data = (PixelPtr *) malloc(sizeof(PixelPtr) *  height);

	/* we use our already created functions to handle a lot of it
	 * which is quite handy =]
	 */
	for(h = 0; h < height; h++) {
		image->data[h] = (PixelPtr) malloc(sizeof(struct Pixel) * width);
		for(w = 0; w < width; w++) {
			(image->data)[h][w] = readPixel(stdin, channel, channel, channel, (char) 255);
		}
	}

	writeImage(image);

	return 0;
}
