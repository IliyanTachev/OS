#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int size = 10;
	char *array = malloc(size*sizeof(char));
	int br=0,max=0,max_length=0;
	for(int i=0;scanf("%c", &array[i]) != EOF;i++)
	{
		//if(array[i] == '\n')br++;
		if(i>=10)
		{
			array = realloc(array,size+2);
			size+=2;
		}
		if(array[i]!='\n')
		{
			max_length++;
		}
		
		else{
			br++;

			if(max_length>max)
			{
				max = max_length;
			}
					
			max_length = 0;
		    }
	}
	//printf("\nBROI NOVI REDOVE: %d",br);
	//printf("max length: %d",max);
	char res_arr[br][max];
	int g=0,f=0;

		for(int z=0;z<br;z++)
		{	
			for(;array[g]!='\n';g++)
			{
				res_arr[z][f] = array[g];
				printf("\narr: %c",array[g]);
				printf("\nres: %c ",res_arr[z][f]);
				f++;	
			}
			g++;
			f=0;
		}
	
	for(int k=0;k<br;k++)
	{	
		//for(int x = 0; x<strlen(res_arr[k]);x++)
		printf("\n%s",res_arr[k]);
	}
	
	free(array);

	return 0;
}
