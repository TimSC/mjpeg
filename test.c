
//gcc utils.c color.c test.c -o test

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main()
{
	FILE *fr = fopen ("test.mjpeg", "rb");
	unsigned char *pic=NULL;

	unsigned char *buf=malloc(63247);
	fread(buf, 1, 63247, fr);
	int width=0;
	int height=0;

	int ret = jpeg_decode(&pic, buf, &width, &height);
	printf("ret %d\n", ret);
	printf("ptr %ld\n", (long) pic);
	printf("height %d\n", height);
	printf("width %d\n", width);

	return 0;
}

