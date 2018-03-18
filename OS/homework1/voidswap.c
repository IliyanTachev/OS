#include<stdio.h>
#include<stdlib.h>
void swap(void *a, void *b, size_t size);
int main()
{
	return 0;
}
void swap(void *a, void *b, size_t size)
{
	char *ptr=malloc(size*sizeof(char));
	char *ptr_a=a;
	char *ptr_b=b;
	/*
	memcpy(ptr,a,size);
	memcpy(a,b,size);
	memcpy(b,ptr,size);	
	*/
	 for(int i=0;i<size;i++)
	 {
		*(ptr+i)=ptr_a[i];
	        *(ptr_a+i)=*(ptr_b+i);
		*(ptr_b+i)=*(ptr+i);
         } 
}
	
