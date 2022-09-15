#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
    printf("started\n");
    pid_t child = fork();
    if (child == 0) {
        char *cmd[] = {"echo-wrong", "hi"};
        execvp(cmd[0], cmd);
        printf("child problem\n");
        exit(1);
    }
    printf("waiting for the child\n");
    int status;
    pid_t finished = wait(&status);
    printf("%d finished\n", finished);
}
