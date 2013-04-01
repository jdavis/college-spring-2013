#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs229.h"

int main(int argc, const char *argv[])
{
	ImagePtr img1, img2;
	PixelPtr p1, p2;
	ushort r1, g1, b1;
	ushort r2, g2, b2;
	FILE *fhImg1, *fhImg2;
	int h, w;

	if (argc != 9) {
		fprintf(stderr, "invalid arguments\nmatte image1 image2 r1 r2 g1 g2 b1 b2\n");
		return 1;
	}

	/* we need two file pointers for each image */
	fhImg1 = fopen(*(++argv), "r");
	fhImg2 = fopen(*(++argv), "r");

	if (fhImg1 == 0 || fhImg2 == 0) {
		fprintf(stderr, "unable to read image\n");
		return 1;
	}
	
	/* yawn, set the rgb values */
	r1 = atoi(*(++argv));
	r2 = atoi(*(++argv));
	g1 = atoi(*(++argv));
	g2 = atoi(*(++argv));
	b1 = atoi(*(++argv));
	b2 = atoi(*(++argv));

	/* create the images and then close the files */
	img1 = readImage(fhImg1);

	if (img1 == NULL) {
		return 1;
	}

	img2 = readImage(fhImg2);

	if (img2 == NULL) {
		return 1;
	}

	fclose(fhImg1);
	fclose(fhImg2);

	/* do some error checking */
	if (img1->bwOrC == 0 && img2->bwOrC == 0) {
		fprintf(stderr, "images should be color\n");
		return 1;
	}

	if (img1->width != img2->width || img1->height != img2->height) {
		fprintf(stderr, "image dimensions don't match\n");
		return 1;
	}

	if (img1->rChannel != img2->rChannel ||
			img1->gChannel != img2->gChannel ||
			img1->bChannel != img2->bChannel) {
		fprintf(stderr, "image channels don't match\n");
		return 1;
	}

	/* no error checking on the r1, r2, etc
	 * it should be up to the user to specify the right values
	 */
	r1 = scale(r1, img1->rChannel, 0);
	r2 = scale(r2, img1->rChannel, 0);
	g1 = scale(g1, img1->gChannel, 0);
	g2 = scale(g2, img1->gChannel, 0);
	b1 = scale(b1, img1->bChannel, 0);
	b2 = scale(b2, img1->bChannel, 0);

	for(h = 0; h < img1->height; h++) {
		for(w = 0; w < img1->width; w++) {
			p1 = &(img1->data[h][w]);
			p2 = &(img2->data[h][w]);
			
			if (p1->r >= r1 && p1->r <= r2 &&
					p1->g >= g1 && p1->g <= g2 && 
					p1->b >= b1 && p1->b <= b2) {

				p1->r = p2->r;
				p1->g = p2->g;
				p1->b = p2->b;
			}
		}
	}

	/* go out into the world, my creation */
	writeImage(img1);
	
	return 0;
}
