#include <stdio.h>
#include <stdlib.h>
#include "cs229.h"
#include "string.h"

void printfImageMeta(int color, int w, int h);
int shouldPrint(int w, int h, int sW, int sH, int r, int c);

int main(int argc, const char *argv[])
{
	int r, g, b;
	int h, w;
	int width, height;
	int sqWidth, sqHeight;
	char colorArg[256];
	int color = 0;
	PixelPtr white = (PixelPtr) malloc(sizeof(struct Pixel));
	PixelPtr pix = (PixelPtr) malloc(sizeof(struct Pixel));

	/* this is kind of lengthy..
	 * It just tests if we want to use stdin or the args and
	 * then it assigns the values and does some testing
	 */
	if (argc == 1) {
		scanf("%s", colorArg);
		scanf("%i %i %i %i %i", &width, &height, &sqWidth, &sqHeight, &r);

		/* only want -color or -bw*/
		if (strcmp("-color", colorArg) == 0) {
			scanf("%i %i", &g, &b);
		} else if (strcmp("-bw", colorArg) != 0) {
			fprintf(stdout, "invalid image type\n");
			return 1;
		}
	} else {
		/* some error checking */
		if (argc < 7 || argc > 9) {
			fprintf(stdout, "invalid number of arguments\n");
			fprintf(stdout, "makesquare: (-color|-bw) width hight sqWidth sqHeight colors\n");
			return 1;
		}
		
		if (strcmp("-color", argv[1]) == 0) {
			color = 255;
		} else if (strcmp("-bw", argv[1]) != 0) {
			fprintf(stdout, "invalid image type\n");
			return 1;
		}

		++argv;
		width = atoi(*(++argv));
		height = atoi(*(++argv));

		sqWidth = atoi(*(++argv));
		sqHeight = atoi(*(++argv));

		r = atoi(*(++argv));

		/* since the pixels are agnostic, we just set g and b to the same values as red if not color*/
		if (color) {
			g = atoi(*(++argv));
			b = atoi(*(++argv));
		} else {
			g = b = r;
		}

		/* make sure they are within value */
		if (r > 255 || r < 0 ||
				g > 255 || g < 0 ||
				b > 255 || b < 0) {
			fprintf(stdout, "invalid image colors\n");
			return 1;
		}

		/* scale to an ushort */
		r = scale(r, 8, 0);
		g = scale(g, 8, 0);
		b = scale(b, 8, 0);
	}
	
	if (sqWidth > width || sqHeight > height) {
		fprintf(stdout, "invalid image dimensions and square dimensions\n");
		return 1;
	}

	if (width < 0 || height < 0) {
		fprintf(stdout, "invalid image dimensions\n");
		return 1;
	}

	if (sqWidth < 0 || sqHeight < 0) {
		fprintf(stdout, "invalid square dimensions\n");
		return 1;
	}


	printfImageMeta(color, width, height);

	white->r = white->g = white->b = 65535;

	/* iterate through the pixels on stdin and then assign them to
	 * a dummy pixel and use our abstracted method to print them
	 * if they aren't in the bounds, print plain white*/
	for(w = 0; w < width; w++) {
		for(h = 0; h < height; h++) {
			if (shouldPrint(width, height, sqWidth, sqHeight, w, h)) {
				pix->r = r;
				pix->g = g;
				pix->b = b;
				writePixel(stdout, pix, 8, 8, 8, color);
			} else {
				writePixel(stdout, white, 8, 8, 8, color);
			}
		}
	}

	return 0;
}

void printfImageMeta(int color, int w, int h) {
	/* 255 = color, rgb channel size = 8, width, height*/
	printf("%c%c%c%c", (color == 255) ? 255 : 0, 8, 8, 8);

	/* print the width and heigth */
	intToChars(w);
	intToChars(h);
}

int shouldPrint(int w, int h, int sW, int sH, int r, int c) {
	int squareR, squareC;

	squareR = (w - sW) / 2;
	squareC = (h - sH) / 2;

	/* make sure we only print when it's in the right bounds */
	if ((r >= squareR && r < squareR + sW) && (c >= squareC && c < squareC + sH)) {
		return 1;
	} else {
		return 0;
	}
}
