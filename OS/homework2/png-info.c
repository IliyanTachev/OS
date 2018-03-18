#include<stdio.h>
#include<stdint.h>
#include<arpa/inet.h>
void *read_image( const char *filepath );
int main(int argc, char** argv)
{
	char *a;
	int i=0;
	if(read_image(argv[1])==NULL)printf("Unable to open file\n");
	else{
		for(a=argv[1];*a!='\0';a++);
		if(*(a-1)=='g' && *(a-2)=='n' && *(a-3)=='p')
		{
			char *ptr=read_image(argv[1]);
			uint32_t *point1=ptr+16;
			uint32_t *point2=ptr+20;
			uint32_t point1_res=ntohl(*point1);
			uint32_t point2_res=ntohl(*point2);
			printf("PNG image width: %d\n",point1_res);
			printf("PNG image height: %d\n",point2_res);
			for(i=0;;i++)
			if(ptr[i]=='I' && ptr[i+1]=='E' && ptr[i+2]=='N' && ptr[i+3]=='D')break;
			printf("PNG file size: %d\n",i+8);
		}
		else printf("Unable to parse file\n");
           }
return 0;
}
