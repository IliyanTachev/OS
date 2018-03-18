#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>

//за обработка на командния ред в рамките на програмата трябва да се дефинира функцията parse_cmdline
char **parse_cmdline( const char *cmdline);

//функцията parse_cmdline() трябва да приеме като аргумент C-string и да връща масив от C–стрингове. Върнатият масив от C-стрингове трябва да бъде оформен така, че да може директно да се подаде като втори аргумент на функция
execv( const char *filename, char *const argv[]);

//за изпълнение на подадените команди трябва да се използва комбинация от обръщания към функциите
pid_t fork( void);
execv( const char *filename, char *const argv[]);

//след завършване на работата на създадения по този начин процес, родителския процес задължително трябва да провери статуса на завършване на детето като използва някой от вариантите на функциите wait*
pid_t waitpid( pid_t pid, int *status, int options);

//командния интерпретатор трябва да позволява организиране на pipe между две или повече приложения/команди
int dup2( int old, int new);

int main() {
		
	/*int size = 100;
	char **words = malloc(size * sizeof(char*));
	char symbol[1];
	char **command;

	while(read(STDIN_FILENO,words,1)) {
		 command = parse_cmdline(words);
	}*/
	char *buffer;
           	const char *res_buffer;
	  
   	   	size_t bufsize = 30;

	   	getline(&buffer,&bufsize,stdin);
	   	printf("==%s ==\n", buffer);
		res_buffer = buffer;

	   	char **result = parse_cmdline(res_buffer);
    	   
		
		 /*printf("\nelement [%d] -> %s",0,result[0]);
		 printf("\nelement [%d] -> %s",1,result[1]);
		 printf("\nelement [%d] -> %s",2,result[2]);
	        */
		pid_t pid;
	        
		pid = fork();
		if(pid < 0) perror("fork");
		else if(pid == 0)
		{
			int res = execv(result[0],result);
			if(res == -1)
			{
				//strcat(error,argv[2])
				perror("error");
				
			}
		}
		else 
		{
			waitpid(pid,0,0);
		}
		exit(pid);

	free(result);
 	 
	return 0;
	
}


char **parse_cmdline( const char *cmdline) {
	int size = 77;
	int size_for_ch = 1;
	char **words =(char**)malloc(size * sizeof(char*)); //kastvame
	//char symbol[1];
	
	//for(int i = 0; i < size; i++) {
		//size = size * 2;
		//words[i] = (char*)malloc(words, size * sizeof(char)); //zadelqme pamet za purviq masiv ot elementi v masiva
	//}
//cmdline - stringa koito podavame na parse_cmdline [purviq red koito si prochel]
	int count = 0;
	int count_for_ch = 0;
	int p = 0; //broi charackters v reda 
//p - sledi ot kraq na minalata duma do nachaloto na novata duma
	int i = 0;//broi dumi 
	//int m = 0;
	for(int k = 0; k < cmdline[k] != '\0'; k++,count++) { //cmdline[k] != '\n'
		//puts("asferfg");
		if(count >= size) {
			size = size * 2;
			words = (char**)realloc(words, size * sizeof(char*));
		}
		words[i] = (char*)malloc(size_for_ch * sizeof(char));
//k - obhojda mi purviq string ot masiva
		while(cmdline[k] != ' ') {
				printf("===================== %ld",strlen(cmdline));
				puts("asferfg");
			if(k == strlen(cmdline) - 1) { break; }
			if( count_for_ch >= size_for_ch) {
				size_for_ch = size_for_ch * 2;
				words[i] = (char*)realloc(words, size_for_ch * sizeof(char*));
			}
			
			for(int m = 0;p < k; p++,m++) { //m - broi characters vuv vsqka duma 
				words[i][m] = cmdline[k]; 
			}
			p = k; //izchakva k-to
		
		}		
			
		//size_for_ch = 1;
		
	}
	size = size * 2;
	words = (char**)realloc(words, size * sizeof(char*));
	words[i] = NULL;
	return words; 
}
