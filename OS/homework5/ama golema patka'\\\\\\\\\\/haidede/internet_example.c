#include<stdio.h>
#include<unistd.h>

int main()
{	
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();

    if(pid==0)
    {
        printf("i'm the child used for ls \n");
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ls", "ls", "-al", NULL);
    }
    else
    { 
        pid=fork();

        if(pid==0)
        {
            printf("i'm in the second child, which will be used to run grep\n");
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            execlp("grep", "grep", "alpha",NULL);
        }
    }

    return 0;
}
