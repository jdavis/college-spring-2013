#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs229.h"

void rotate(int a, int h, int w, int height, int width, int *nH, int *nW);

int main(int argc, const char *argv[])
{
	int w, h, angle, nW, nH;
	int newWidth, newHeight;
	ImagePtr image, rotated;
	PixelPtr p1, p2;

	/* check and validate args first */
	if (argc != 2) {
		fprintf(stderr, "invalid arguments\nflip angle < image\n");
		return 1;
	}


	/* get the angle and verify it is valid */
	angle = atoi(argv[1]);

	if (angle != 90 && angle != 180 && angle != -90) {
		fprintf(stderr, "invalid angle\nonly 90, -90, and 180 accepted\n");
		return 1;
	}

	image = readImage(stdin);

	if (image == NULL) {
		return 1;
	}

	newWidth = angle == 180 ? image->width : image->height;
	newHeight = angle == 180 ? image->height : image->width;

	rotated = emptyImage(newHeight, newWidth);

	/* copy over the values */
	rotated->rChannel = image->rChannel;
	rotated->gChannel = image->gChannel;
	rotated->bChannel = image->bChannel;
	rotated->bwOrC = image->bwOrC;

	/* I use a function that just has the values hardcoded for what they values should be
	 * the new values are returned using pointers */
	for(h = 0; h < image->height; h++) {
		for(w = 0; w < image->width; w++) {
			rotate(angle, h, w, image->height, image->width, &nH, &nW);
			
			/* pic the new pixels we need and swap them */
			p1 = &(image->data[h][w]);
			p2 = &(rotated->data[nH][nW]);

			swapPixels(p1, p2);
		}
	}

	writeImage(rotated);
	
	return 0;
}

/* it uses pointers to return the values so I only have to call it once
 * depending on the angles, it just performs the correct math for the pixel's
 * new location, easy peasy
 */
void rotate(int a, int h, int w, int height, int width, int *nH, int *nW) {
	switch(a) {
		case -90:
			*nW = h;
			*nH = width - w - 1;
			break;
		case 0:
			*nW = w;
			*nH = h;
			break;
		case 90:
			*nW = height - h - 1;
			*nH = w;
			break;
		case 180:
			*nW = w;
			*nH = height - h - 1;
			break;
	}
}
