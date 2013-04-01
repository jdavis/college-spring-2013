#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs229.h"

float **makeKernel(FILE *fh, int *s);
ushort convolve(ImagePtr image, int i, int j, float **kernel, int kSize, int rgb);
int inBounds(ImagePtr image, int i, int j);

int main(int argc, const char *argv[])
{
	ImagePtr image;
	ImagePtr result;
	FILE *kfile;
	int rSize, gSize, bSize;
	int h, w;
	float **rKernel;
	float **gKernel;
	float **bKernel;
	PixelPtr pix;

	if (argc != 2) {
		fprintf(stderr, "invalid arguments\nconvolve kfile < image\n");
		return 1;
	}

	image = readImage(stdin);

	if (image == NULL) {
		return 1;
	}

	result = emptyImage(image->height, image->width);

	/* copy over the values */
	result->rChannel = image->rChannel;
	result->gChannel = image->gChannel;
	result->bChannel = image->bChannel;
	result->bwOrC = image->bwOrC;

	/* check our kfile */
	kfile = fopen(argv[1], "r");

	if (kfile == NULL) {
		fprintf(stderr, "invalid kernel file\n");
		return 1;
	}

	/* putting the kernel creation in a function saves a lot of space */
	rKernel = makeKernel(kfile, &rSize);
	gKernel = makeKernel(kfile, &gSize);
	bKernel = makeKernel(kfile, &bSize);

	/* error check our kernels */
	if (image->bwOrC == 0 && (rKernel == 0 || gKernel != 0 || bKernel != 0)) {
		fprintf(stderr, "invalid kernel file for black and white image\n");
		return 1;
	}

	if (image->bwOrC != 0 && (rKernel == 0 || gKernel == 0 || bKernel == 0)) {
		fprintf(stderr, "invalid kernel file for color image\n");
		return 1;
	}

	for(h = 0; h < image->height; h++) {
		for(w = 0; w < image->width; w++) {
			/* the pixel we want to change */
			pix = &(result->data[h][w]);

			/* we only need to convolve the r if the image is bw */
			pix->r = convolve(image, h, w, rKernel, rSize, 0);
			
			/* convolve the bg if color */
			if (image->bwOrC != 0) {
				pix->g = convolve(image, h, w, gKernel, gSize, 1);
				pix->b = convolve(image, h, w, bKernel, bSize, 2);
			}
		}
	}

	writeImage(result);
	
	return 0;
}

/* performs the kernel file on the given image pixel */
ushort convolve(ImagePtr image, int i, int j, float **kernel, int kSize, int rgb) {
	int h, w, nH, nW;
	float x = 0;
	ushort sum;

	/* the current pixel we are "centered" on */
	PixelPtr p;

	/* go through each kernel value and then
	 * perform the operation on the specific pixel
	 */
	for(h = 0; h < kSize; h++) {
		for(w = 0; w < kSize; w++) {
			/* the right coordinate for the specified kernel value */
			nH = i + h - kSize/2;
			nW = j + w - kSize/2;

			/* make sure we are in bounds */
			if (inBounds(image, nH, nW) && x != 65535) {
				p = &(image->data[nH][nW]);

				/* use the right pixel value depending on whether we're working with r, g, b */
				switch(rgb) {
					case 0:
						x += kernel[h][w] * (float) p->r;
						break;
					case 1:
						x += kernel[h][w] * (float) p->g;
						break;
					case 2:
						x += kernel[h][w] * (float) p->b;
						break;
				}
			}

		}
	}

	/* we only want the max if it happens to be bigger than the max value */
	if (x > 65535) {
		sum = 65535;
	} else {
		/* this should round it correctly.. */
		sum = (ushort) x + .5;
	}

	return sum;
}

int inBounds(ImagePtr image, int i, int j) {
	/* make sure the values are within the image */
	if (i < 0 || i >= image->height) return 0;
	else if (j < 0 || j >= image->width) return 0;
	else return 1;
	
}

float **makeKernel(FILE *fh, int *s) {
	int kernelSize;
	int h, w;
	float **kernels;
	float k;

	if (fscanf(fh, "%i", &kernelSize) == EOF) {
		return 0;
	}

	/* make sure the kernel size is odd */
	if (!(kernelSize & 0x1)) {
		fprintf(stderr, "invalid kernel size\n");
		return 0;
	}

	/* the spec says to only allow kernels between 3 and 15 */
	if (kernelSize > 15 || kernelSize < 3) {
		fprintf(stderr, "invalid kernel size\n");
		return 0;
	}

	/* return the kernel size back to the user */
	*s = kernelSize;
	
	/* this dynamically creates our kernels */
	kernels = (float **) malloc(sizeof(float *) *  kernelSize);

	for(h = 0; h < kernelSize; h++) {
		kernels[h] = (float *) malloc(sizeof(float) * kernelSize);
		for(w = 0; w < kernelSize; w++) {
			if (fscanf(fh, "%f", &k) == EOF) {
				return 0;
			}
			kernels[h][w] = k;
		}
	}

	/* 'Kernel' Sanders even approves of this function */
	return kernels;
	/* har har, just kidding */
}
