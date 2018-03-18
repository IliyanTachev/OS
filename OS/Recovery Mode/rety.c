#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

char **parse_cmdline( const char *cmdline ) {
	printf("commandline\n");
	int size = 1;
	int chsize = 1;
	int a = 0;
	int k = 0;
	//char command[100][100];
	printf("commandline\n");
	//printf ("cmdline %s\n",cmdline);
	char **command;
	command = (char **)malloc(size * sizeof(char*));
	command[a] = (char *)malloc(chsize * sizeof(char));
	int i;
	for (i = 0; 1 ; i++) {
		if (cmdline[i] == ' ' || cmdline[i] == '\n') {
			if (cmdline[i] == '\n') {break;}
			if (size >= a ) {
				size ++;
				command = (char **)realloc(command, size*sizeof(char*));
				//printf ("size realloc %d\n",size);
			}
			//printf ("%s\n", command[a]);
			chsize = 1;
			k = 0;
			command[++a] = (char *)malloc(chsize * sizeof(char));
			continue;
		}

		
		if (chsize >= k) {
			chsize ++;
			command[a] = (char *)realloc(command[a], chsize);
			//printf ("chsize realloc %d\n",chsize);
		}
		command[a][k++] = cmdline[i];
		//command[a][k] = '\0';
		//printf ("%d",i+1);
		
	}
	//printf ("%d\n",size);
	//printf ("%ld",sizeof(char*));
	//printf ("%d\n",strlen(cmdline));
//int f = 0;	
	size ++;
	command = (char **)realloc(command, size*sizeof(char*));
	command[++a] = NULL;
return command;
}

int main () {
	
	//char** command;
		char *word;
		const char *helper;
		size_t word_size = 30;
		getline(&word,&word_size,stdin);
		helper = word;
		char **command = parse_cmdline(helper);	

		 printf("\nelement [%d] -> %s",0,command[0]);
		 printf("\nelement [%d] -> %s",1,command[1]);
		 printf("\nelement [%d] -> %s",2,command[2]);

	pid_t pid = fork();
	
		if (pid < 0) {

			perror ("fork");
		}
		else if (pid == 0) {
			//int result = execl(command[0],"/bin/ls",0);
			int result = execv(command[0],command);
			if (result < 0) perror ("execv");
		
		}

		else {
			waitpid(pid,0,0);
		}
		exit(pid);
	
	free (command);
return 0;
}
