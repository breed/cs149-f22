#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("USAGE: %s filename\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror(argv[1]);
        exit(2);
    }
    printf("fd = %d\n", fd);
    dup2(fd, 1);
    dup2(fd, 2);
    char message[] = "goodbye\n";
    write(1, message, strlen(message));
    printf("you say goodbye and i say hello\n");
    fprintf(stderr, "what?\n");
    close(fd);
}
