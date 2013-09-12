
//gcc utils.c color.c test.c -o test

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void WritePPMImage(const char *fina, unsigned char *img, int height, int width)
{
	int i, j, cursor = 0;
	FILE *fp = fopen(fina, "wb"); /* b - binary mode */
	(void) fprintf(fp, "P6\n%d %d\n255\n", width, height);
	for (j = 0; j < height; ++j)
	{
		for (i = 0; i < width; ++i)
		{
			static unsigned char color[3];
			color[0] = img[cursor];	/* red */
			color[1] = img[cursor];	/* green */
			color[2] = img[cursor];	/* blue */
			(void) fwrite(color, 1, 3, fp);
			cursor += 2;
		}
	}
	(void) fclose(fp);
}

int main()
{
	//Read input data
	FILE *fr = fopen ("test.mjpeg", "rb");
	unsigned char *pic=NULL;

	unsigned char *buf=malloc(63247);
	fread(buf, 1, 63247, fr);
	int width=0;
	int height=0;

	//Decode MJPEG to YUYV buffer(?)
	int ret = jpeg_decode(&pic, buf, &width, &height);
	printf("ret %d\n", ret);
	printf("ptr %ld\n", (long) pic);
	printf("height %d\n", height);
	printf("width %d\n", width);
	
	//Write greyscale (Y) information as PPM image
	if (pic != NULL)
	{
		WritePPMImage("test.ppm", pic, height, width);
		printf("Written test.ppm\n");
	}

	return 0;
}

