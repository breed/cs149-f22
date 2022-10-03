#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char first_char;
    char *shared_first_char;

    if (argc != 2) {
        printf("USAGE: %s filename\n", argv[0]);
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror(argv[1]);
        exit(2);
    }
    struct stat stat;
    if (fstat(fd, &stat) == -1) {
        perror(argv[1]);
        exit(2);
    }
    shared_first_char = mmap(NULL, 1, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    if (shared_first_char == NULL) {
        perror(argv[1]);
        exit(2);
    }

    printf("shared first char is %p\n", shared_first_char);

    *shared_first_char = '?';
    first_char = '?';

    if (fork() == 0) {
        char *ptr = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (ptr == NULL) {
            perror(argv[1]);
            exit(2);
        }
        printf("ptr is %p\n", ptr);

        first_char = *ptr;
        *shared_first_char = *ptr;
        printf("first 5 chars are %s\n", ptr);
        printf("child first_char is %c shared_first_char is %c\n", first_char, *shared_first_char);
        sleep(200);
        exit(0);
    }

    wait(NULL);
    printf("first_char is %c shared_first_char is %c\n", first_char, *shared_first_char);
    sleep(200);
}
