#include "cs229.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define UPC_HEIGHT .3333f

int getValue(int b[], int left);
int lookForVerticalUPC(ImagePtr i, int h, int w);
int closeToBlack(PixelPtr p);
int closeToPixel(PixelPtr p, PixelPtr c, int debug);
int average(int x, int y, int z);
int checkBarCode(int codes[]);
int valueForBars(int bars[], int estWidth, int contrast, int left);

int main(int argc, const char *argv[])
{
	ImagePtr image = readImage(stdin);
	int w, h = 2;
	int foundUPC = 0;
	
	if (image == NULL) {
		return 1;
	}


	for(h = 0; h < image->height; h++) {
		if (foundUPC) break;

		for(w = 0; w < image->width; w++) {
			foundUPC = lookForVerticalUPC(image, h, w);

			if (foundUPC) break;
		}
	}

	return 0;
}


int lookForVerticalUPC(ImagePtr i, int h, int w) {
	int height = 0;
	int scanHeight = h;
	int height_tolerance;
	int pIndex = 0;
	int bIndex = 0;
	int currentWidth = 1;
	int barWidth;
	int contrast = 1;
	int barWidths[4];
	int barCodes[12];
	int barCodesIndex = 0;
	int left = 1;
	int barCode[12];
	int pp;
	bIndex = 0;

	

	while(closeToBlack(&(i->data[h][w])) && h + 1 < i->height) {
		h++;
		height++;
	}


	height_tolerance = i->height / 5;
	if (!(height >= height_tolerance)) {
		return 0;
	}

	scanHeight += UPC_HEIGHT * height;


	while(pIndex < 15 && (w + 1 < i->width) && scanHeight < i->height) {
		PixelPtr currentPix = &(i->data[scanHeight][w]);
		PixelPtr nextPix = &(i->data[scanHeight][w + 1]);

		if (pIndex == 7) {
			if (bIndex == 5) {
				pIndex++;
				bIndex = 0;
				left = 0;
			}
		}

		if (!closeToPixel(currentPix, nextPix, 0)) {
			contrast = !contrast;

			barWidths[bIndex++] = currentWidth;
			w++;
			currentWidth = 1;

			if (bIndex == 4 && pIndex != 7) {
				barCodes[barCodesIndex] = valueForBars(barWidths, barWidth, contrast, left);
				bIndex = 0;
				pIndex++;
				barCodesIndex++;
			} else if (bIndex == 3 && (pIndex == 0 || pIndex == 14) && pIndex != 7) {
				if (pIndex == 0) {
					barWidth = average(barWidths[0], barWidths[1], barWidths[2]);
				}

				bIndex = 0;
				pIndex++;
				contrast = 0;
			}
		} else {
			currentWidth++;
			w++;
		}
	}

	for(pp = 1; bIndex < 12 && pp < pIndex - 2; pp++) {
		if (pp != 7) {
			barCode[bIndex] = -1;
			bIndex++;
		}
	}

	
	return checkBarCode(barCodes);
}

int checkBarCode(int codes[]) {
	int x, f;
	int isValid = 1;
	for(f = 0; f < 12; f++) {
		if (codes[f] == -1) {
			isValid = 0;
		}
	}


	if (isValid) {
		for(f = 0; f < 12; f++) {
			x = codes[f];
			if (x == -1) {
				isValid = 0;
			}
			printf("%i", x);
		}
		printf("\n");
	}
	return isValid;
}

int valueForBars(int bars[], int estWidth, int contrast, int left) {
	int bits[7];
	int d;
	int value;

	int f, bIndex = 0;
	int i;
	for(f = 0; f < 4; f++) {
		int w = bars[f];

		if ((w / estWidth) >= 5) {
			w = estWidth * 4;
		}
		d = (float) w / estWidth + .5;
		for(i = 0; i < d; i++) {
			bits[bIndex++] = contrast;
		}
		contrast = !contrast;
	}

	value = getValue(bits, left);
	return value;
}

int getValue(int b[], int left) {

	int f, i;

	int result = 1;
	int leftA[10][7] = {
		{0, 0, 0, 1, 1, 0, 1},
		{0, 0, 1, 1, 0, 0, 1},
		{0, 0, 1, 0, 0, 1, 1},
		{0, 1, 1, 1, 1, 0, 1},
		{0, 1, 0, 0, 0, 1, 1},
		{0, 1, 1, 0, 0, 0, 1},
		{0, 1, 0, 1, 1, 1, 1},
		{0, 1, 1, 1, 0, 1, 1},
		{0, 1, 1, 1, 0, 1, 1},
		{0, 0, 0, 1, 0, 1, 1},
	};
	int rightA[10][7] = {
		{1, 1, 1, 0, 0, 1, 0},
		{1, 1, 0, 0, 1, 1, 0},
		{1, 1, 0, 1, 1, 0, 0},
		{1, 0, 0, 0, 0, 1, 0},
		{1, 0, 1, 1, 1, 0, 0},
		{1, 0, 0, 1, 1, 1, 0},
		{1, 0, 1, 0, 0, 0, 0},
		{1, 0, 0, 0, 1, 0, 0},
		{1, 0, 0, 1, 0, 0, 0},
		{1, 1, 1, 0, 1, 0, 0},
	};

	result = 1;
	for(f = 0; f < 10; f++) {
		int result = 1;
		for(i = 0; i < 7; i++) {
			if (left) {
				if (leftA[f][i] != b[i]) {
					result = 0;
				}
			} else {
				if (rightA[f][i] != b[i]) {
					result = 0;
				}
			}
		}

		if (result == 1) {
			return f;
		}
	}

	return -1;
}


int closeToPixel(PixelPtr p, PixelPtr c, int debug) {
	int tolerance = 32000;
	int rt, gt, bt;

	if (p == NULL) printf("p == null\n");
	if (c == NULL) printf("p == null\n");
	rt = p->r - c->r;
	gt = p->g - c->g;
	bt = p->b - c->b;

	rt = rt < 0 ? -rt : rt;
	gt = gt < 0 ? -gt : gt;
	bt = bt < 0 ? -bt : bt;


	if (rt > tolerance) {
		return 0;
	} else if (gt > tolerance) {
		return 0;
	} else if (bt > tolerance) {
		return 0;
	}

	return 1;
}

int closeToBlack(PixelPtr p) {
	int tolerance = 29000;

	if (p->r > tolerance) {
		return 0;
	} else if (p->g > tolerance) {
		return 0;
	} else if (p->b > tolerance) {
		return 0;
	}

	return 1;
}

int average(int x, int y, int z) {
	float sum;

	sum = x + y + z;
	sum /= 3;

	return sum + .5;
}
