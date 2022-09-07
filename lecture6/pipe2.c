#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fds[2];
    pipe(fds);
    if (fork() == 0) {
        printf("%d: sleeping before writing\n", getpid());
        sleep(2);
        printf("%d: writing hi\n", getpid());
        write(fds[1], "hi", 2);
        sleep(2);
        printf("%d: exiting\n", getpid());
        exit(0);
    } else {
        printf("%d: reading\n", getpid());
        char buffer[1024];
        int rc = read(fds[0], buffer, sizeof buffer);
        buffer[rc] = '\0';
        printf("%d: read %d bytes -> %s\n", getpid(), rc, buffer);

        printf("%d: reading\n", getpid());
        rc = read(fds[0], buffer, sizeof buffer);
        buffer[rc] = '\0';
        printf("%d: read %d bytes -> %s\n", getpid(), rc, buffer);
    }
}
