#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

void handle_signal(int signum)
{
    printf("got signal %d\n", signum);
    printf("continuing execution\n");
}

int main()
{
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(2);
    }
    if (pid == 0) {
        signal(SIGINT, handle_signal);
        while (1) {
            printf("sleeping\n");
            sleep(100);
        }
    }
    printf("child started pid = %d\n", pid);
    sleep(2);
    kill(pid, SIGTERM);
    sleep(3);
    kill(pid, SIGKILL);
    int status;
    int finished_pid = wait(&status);
    printf("%d finished\n", finished_pid);
    if (WIFEXITED(status)) {
        printf("%d exited with %d\n", finished_pid, WEXITSTATUS(status));
    } else {
        printf("%d kill by signal %d\n", finished_pid, WTERMSIG(status));
    }
}
