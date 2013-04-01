#include "cs229.h"
#include <stdio.h>
#include <stdlib.h>

int charsToInt(FILE *fh);
ushort readChannel(FILE *fh, char channel);
void writeShort(FILE *fh, ushort r, int c, int endOfFile);
void printPixel(PixelPtr p);

ImagePtr readImage(FILE *fh) {
	char bwOrColor;
	char rChannel, gChannel, bChannel;
	int width, height;
	int w, h;
	int fscanRet;

	ImagePtr image = (ImagePtr) malloc(sizeof(struct Image));

	/* uh ohs */
	if (!image) {
		fprintf(stderr, "Memory unable to allocate\n");
		return 0;
	}

	/* read in the image information and set the right values */

	fscanRet = fscanf(fh, "%c%c%c%c", &bwOrColor, &rChannel, &gChannel, &bChannel);

	if (fscanRet == EOF) {
		fprintf(stderr, "invalid image\n");
		return 0;
	}

	if (bwOrColor != -1 && bwOrColor != 0) {
		fprintf(stderr, "invalid image type\n");
		return 0;
	}

	if (rChannel != 4 && rChannel != 8 &&
			rChannel != 12 && rChannel != 16) {
		fprintf(stderr, "invalid image red channel\n");
		return 0;
	}

	if (gChannel != 4 && gChannel != 8 &&
			gChannel != 12 && gChannel != 16) {
		fprintf(stderr, "invalid image green channel\n");
		return 0;
	}

	if (bChannel != 4 && bChannel != 8 &&
			bChannel != 12 && bChannel != 16) {
		fprintf(stderr, "invalid image blue channel\n");
		return 0;
	}

	width = charsToInt(fh);
	height = charsToInt(fh);

	if (width <= 0 ||
			height <= 0) {
		fprintf(stderr, "invalid image\n");
		return 0;
	}
	
	image->width = width;
	image->height = height;
	image->bwOrC = bwOrColor;
	image->rChannel = rChannel;
	image->gChannel = gChannel;
	image->bChannel = bChannel;

	/* create the pixel data and start setting the pixels */
	image->data = (PixelPtr *) malloc(sizeof(PixelPtr) *  height);

	for(h = 0; h < height; h++) {
		image->data[h] = (PixelPtr) malloc(sizeof(struct Pixel) * width);
		for(w = 0; w < width; w++) {
			(image->data)[h][w] = readPixel(fh, rChannel, gChannel, bChannel, bwOrColor);
		}
	}

	return image;
}

ImagePtr emptyImage(int height, int width) {
	int h;
	ImagePtr image = (ImagePtr) malloc(sizeof(struct Image));
	if (!image) {
		fprintf(stderr, "Memory unable to allocate");
		exit(1);
	}


	image->data = (PixelPtr *) malloc(sizeof(PixelPtr) *  height);
	image->height = height;
	image->width = width;

	for(h = 0; h < height; h++) {
		image->data[h] = (PixelPtr) malloc(sizeof(struct Pixel) * width);
	}

	return image;
}

void intToChars(int x) {
	int i;
	char c;

	for(i = 3; i >= 0; i--) {
		c = (char) 0xFF;
		c = x >> (i * 8);
		printf("%c", c);
	}
}

int charsToInt(FILE *fh) {
	unsigned char i, c;
	int result;
	int fscanRet;
	result = 0;
	for(i = 0; i < 4; i++) {
		fscanRet = fscanf(fh, "%c", &c);
		if (fscanRet == EOF) {
			return 0;
		}
		result = result << 8;
		result |= c;
	}

	return result;
}

void writeImage(ImagePtr image) {
	int h, w;
	PixelPtr p;
	
	printf("%c%c%c%c", image->bwOrC, image->rChannel, image->gChannel, image->bChannel);

	intToChars(image->width);
	intToChars(image->height);

	for(h = 0; h < image->height; h++) {
		for(w = 0; w < image->width; w++) {
			p = &(image->data[h][w]);
			writePixel(stdout, p, image->rChannel, image->gChannel, image->bChannel, image->bwOrC);
		}
	}
	writeShort(stdout, 0, 0, 1);
}

void printImageMeta(ImagePtr i) {
	printf("Image: %s - ", (i->bwOrC == 255) ? "Color" : "Black and White");
	printf("%ix%i\n", i->width, i->height);
	printf("Channels: %i, %i, %i\n", i->rChannel, i->gChannel, i->bChannel);
}

PixelPtr getPixel(ImagePtr i, int w, int h) {
	return &(i->data[w][h]);
}

void printPixel(PixelPtr p) {
	printf("PixelPtr: %i,%i,%i\n", p->r, p->g, p->b);
}

struct Pixel readPixel(FILE *fh, char rc, char gc, char bc, char bwOrColor) {
	struct Pixel pix;

	/*pix.bwOrC = bwOrColor;*/

	pix.r = readChannel(fh, rc);

	if (bwOrColor == 0) {
		pix.g = pix.r;
		pix.b = pix.r;
	} else {
		pix.g = readChannel(fh, gc);
		pix.b = readChannel(fh, bc);
	}

	return pix;
}

void swapPixels(PixelPtr p1, PixelPtr p2) {
	int rt, gt, bt;
	/*int bw;*/
	rt = p1->r;
	gt = p1->g;
	bt = p1->b;
	/*bw = p1->bwOrC;*/
	
	p1->r = p2->r;
	p1->g = p2->g;
	p1->b = p2->b;
	/*p1->bwOrC = p2->bwOrC;*/

	p2->r = rt;
	p2->g = gt;
	p2->b = bt;
	/*p2->bwOrC = bw;*/
}

void writePixel(FILE *fh, PixelPtr p, char rc, char gc, char bc, char bwOrColor) {
	writeShort(fh, p->r, rc, 0);

	if (bwOrColor != 0) {
		writeShort(fh, p->g, gc, 0);
		writeShort(fh, p->b, bc, 0);
	}
}

void writeShort(FILE *fh, ushort r, int c, int endOfFile) {
	static char unread = 0;
	static int useUnread = 0;
	ushort s;

	if (useUnread && endOfFile) {
		fprintf(fh, "%c", unread << 4);
		return;
	}

	s = scale(r, c, 1);

	switch(c) {
		case 4:
			if (useUnread) {
				unread <<= 4;
				fprintf(fh, "%c", unread | s);
				unread = useUnread = 0;
			} else {
				unread = s;
				useUnread = 1;
			}
			break;
		case 8:
			if (useUnread) {
				unread <<= 4;
				fprintf(fh, "%c", unread | (s >> 4));
				unread = s & 0x0F;
			} else {
				fprintf(fh, "%c", s);
			}
			break;
		case 12:
			if (useUnread) {
				unread <<= 4;
				fprintf(fh, "%c", unread | (s >> 8));
				fprintf(fh, "%c", s & 0x00FF);
				useUnread = unread = 0;
			} else {
				fprintf(fh, "%c", s >> 4);
				unread = s & 0xF;
				useUnread = 1;
			}
			break;
		case 16:
			if (useUnread) {
				useUnread <<= 4;
				fprintf(fh, "%c", useUnread | (s >> 12));
				fprintf(fh, "%c", s >> 4);
				useUnread = 1;
				unread = s & 0xF;
			} else {
				fprintf(fh, "%c%c", s >> 8, s);
			}
			break;
	}
}

ushort readChannel(FILE *fh, char channel) {
	unsigned char c, c2;
	ushort r;
	static char unread = 0;
	static int useUnread = 0;

	switch(channel) {
		case 4:
			if (useUnread) {
				r = unread;
				unread = useUnread = 0;
			} else {
				fscanf(fh, "%c", &c);

				r = c & 0xF0;
				r >>= 4;
				unread = c & 0x0F;
				useUnread = 1;
			}
			break;
		case 8:
			fscanf(fh, "%c", &c);
			if (useUnread) {
				r = unread;
				r <<= 4;
				r |= (c & 0xF0) >> 4;
				useUnread = 1;
				unread = c & 0x0F;
			} else {
				r = c;
			}
			break;
		case 12:
			fscanf(fh, "%c", &c);
			if (useUnread) {
				r = unread;
				r <<= 8;
				r |= c;
				useUnread = unread = 0;
			} else {
				fscanf(fh, "%c", &c2);
				r = c << 4;
				r |= (c2 >> 4);
				unread = c2 & 0x0F;
				useUnread = 1;
			}
			break;
		case 16:
			fscanf(fh, "%c", &c);
			fscanf(fh, "%c", &c2);
			if (useUnread) {
				r = unread << 12;
				r |= c << 4;
				r |= c2 >> 4;
				
				unread = c2 & 0x0F;
			} else {
				r = c << 8;
				r |= c2;
			}
			break;
	}

	return scale(r, channel, 0);
}

int pow2(int e) {
	int r = 1;
	while (e-- >= 1) r <<= 1;

	return r;
}

ushort scale(ushort s, char c, char u) {
	int p, scalar;
	if (c == 16 || s == 0) return s;
	p = pow2(c) - 1;
	scalar = 65535 / p;

	return u ? s / scalar : s * scalar;
}
