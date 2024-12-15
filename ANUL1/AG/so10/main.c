#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
    int pid = fork();
    if (pid == -1)                      // fork() failed
    {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)                       // in child process
    {
        printf("\n[In CHILD] I started ...\n");
        int i;
        for (i = 0; i < 3; i++)
        {
	        sleep(5);
	        printf("[In CHILD]\tMy PID is %d Parent PID is %d\n", getpid(), getppid());
    	}
    	printf("[In CHILD] I finished my job.\n");
    	printf("\n[In CHILD]\tI am in the ZOMBIE state now ...\n");
    	printf("[In CHILD]\tCould you killed me, please ?\n");
    }
    else                                // in parent process
    {
    	printf("[In PARENT] I started ...\n");
        printf("[In PARENT]\tMy PID is %d Child PID is %d\n", getpid(), pid);
        while(1);
        printf("[In PARENT] I finished.\n");
    }
    return 0;
}
