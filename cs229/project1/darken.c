#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cs229.h"

void darken(PixelPtr p, int percent);
void lighten(PixelPtr p, int percent);

int main(int argc, const char *argv[])
{
	int w, h, l, shouldDarken, percent;
	char id;
	ImagePtr image;
	PixelPtr p;
	/* check our args */
	if (argc != 2) {
		fprintf(stderr, "invalid arguments\n(darken|lighten) percent < image\n");
		return 1;
	}

	/* determine if we should darken or lighten by using the 3rd to last char in the program name*/
	l = strlen(argv[0]);

	if (l < 3) {
		fprintf(stderr, "lighten or darken function unknown\ninvalid program name\n");
		return 1;
	}

	id = tolower((argv[0])[l - 3]);

	/* darKen = darken()
	 * lighTen = lighten()
	 */
	if (id == 'k') {
		shouldDarken = 1;
	} else if (id == 't') {
		shouldDarken = 0;
	} else {
		fprintf(stderr, "lighten or darken function unknown\ninvalid program name\n");
		return 1;
	}

	image = readImage(stdin);

	if (image == NULL) {
		return 1;
	}

	percent = atoi(argv[1]);

	/* check percentages */
	if (percent > 100 || percent < 0) {
		fprintf(stderr, "invalid percentage, 0 - 100\n");
		return 1;
	}

	/* iterate through each pixel and perform the operation */
	for(h = 0; h < image->height; h++) {
		for(w = 0; w < image->width; w++) {
			p = &(image->data[h][w]);
			if (shouldDarken) darken(p, percent);
			else lighten(p, percent);
		}
	}

	/* push it to stdout */
	writeImage(image);
	
	return 0;
}

void darken(PixelPtr p, int percent) {
	/* use the difference between lowest and multiply by the percentage then subtract */
	p->r -= p->r * (float) percent / 100.0;
	p->g -= p->g * (float) percent / 100.0;
	p->b -= p->b * (float) percent / 100.0;
}

void lighten(PixelPtr p, int percent) {
	/* use the difference between highest value and multiply by the percentage then add */
	p->r += (65535 - p->r) * (float) percent / 100.0;
	p->g += (65535 - p->g) * (float) percent / 100.0;
	p->b += (65535 - p->b) * (float) percent / 100.0;
}
