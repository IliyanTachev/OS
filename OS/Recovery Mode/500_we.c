#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>

//за обработка на командния ред в рамките на програмата трябва да се дефинира функцията parse_cmdline
char **parse_cmdline( const char *cmdline);

int main() {
	while(1)
	{	
		write(1,"$ ",2);
	
	
		char *buffer = NULL;
	  
   	   	size_t bufsize = 0;
		getline(&buffer,&bufsize,stdin);
		
		if(feof(stdin)) {
		
			free(buffer);
			break;
		}

		
	   	
	   	char **result = parse_cmdline(buffer); 
    	   	free(buffer);
		pid_t pid;
	        
		pid = fork();
		if(pid < 0) 
		{
			perror("fork");

			int i = 0;
			for(; result[i] != NULL; i++)
			{
				free(result[i]);
			}

				
				free(result);
		}
		else if(pid == 0)
		{
			int res = execv(result[0],result);
			if(res == -1)
			{
				
				perror(result[0]);
				int i = 0;
				for(; result[i] != NULL; i++) {
					free(result[i]);
				}

				//free(result[i]);
				free(result);

				
				exit(0);
			}
			
		}
		else 
		{
			waitpid(pid,0,0);
			int i = 0;
			for(; result[i] != NULL; i++) {
				free(result[i]);
			}

			free(result);
		}
		
		

 	}
	
	
	
	return 0;
	
}


char **parse_cmdline(const char *cmdline) {

	int size = 40; //size-a na celiq red
	int el_size = 3; //size-a na elementite dokato sreshtne space
	char **words = (char**)malloc(size * sizeof(char*)); //zadelqne na pamet za celiq red + kastvane kum char
	int count = 0; //promenliva za proverka za reallocirane na reda
	int el_count = 0; //promenliva za proverka za reallocirane na dumata
	int i = 0; //broqch na koq duma se namirame	
	int m=0;
	int true_tmp=1;
	
	for(int k = 0; cmdline[k] != '\0'; count++)
	 { 
		if(count >= size) 
		{ 
			size = size + 2; //uvelichavame size-a 2 puti i posle reallokirame
			words = realloc(words, size * sizeof(char*)); //reallocirame
		}
		//zadelqme pamet za edin string ot masiva
		//write(1,"9",1);
		
		while(cmdline[k] != ' ') {
			//int m = 0;
			 //hardcode
			//write(1,"2",1);
			if(cmdline[k]=='\n'){ break; }
			//if(cmdline[k] == ' ') { break; }
			if(true_tmp){words[i] = malloc(el_size * sizeof(char));}
			true_tmp = 0;
			//write(1,"1",1);

			words[i][el_count] = cmdline[k];
			el_count++;
			k++;
			if(el_count >= el_size) { //count_for_ch >= size_for_ch
				el_size= el_size + 2; //uvelichavame size-a za edin string 2 puti i posle reallokirame
				words[i] = realloc(words[i], el_size * sizeof(char)); //reallocirame za edin string ot masiva
			}
		}
		if(!true_tmp){i++;}
		
		true_tmp=1;
		k++;el_count=0;el_size=2;
				
	}

	words[i] = NULL;
	return words;
}
