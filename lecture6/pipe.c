#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fds[2];
    write(1, "i'm writing to 1!!!\n", 10);
    pipe(fds);
    printf("pipe gave us %d and %d\n", fds[0], fds[1]);
    printf("%d: writing hi\n", getpid());
    write(fds[1], "hi", 2);
    char buffer[1024];
    int rc = read(fds[0], buffer, sizeof buffer);
    buffer[rc] = '\0';
    printf("%d: read %d bytes -> %s\n", getpid(), rc, buffer);
}
