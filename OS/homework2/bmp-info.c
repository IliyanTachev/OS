#include<stdio.h>
#include<stdint.h>
void *read_image( const char *filepath );
int main(int argc,char **argv)
{
	char *ptr=read_image(argv[1]);
	uint32_t *point1=ptr+18;
	uint32_t *point2=ptr+22;
	printf("BMP image width: %d\n",*(point1));
	printf("BMP image height: %d\n",*(point2));
	return 0;
}
