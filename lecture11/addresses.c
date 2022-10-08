#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    void *small_malloc = malloc(10);
    void *p1 = malloc(65536);
    void *p2 = malloc(65536);
    free(p1);
    void *big_malloc = malloc(256*1024*1024);
    printf("my pid is %d\n", getpid());
    printf("main is at %p\n", main);
    printf("malloc is at %p\n", malloc);
    printf("small_malloc is at %p\n", &small_malloc);
    printf("big_malloc is at %p\n", &big_malloc);
    printf("small_malloc points to %p\n", small_malloc);
    printf("big_malloc points to %p\n", big_malloc);
    sleep(10*60);
}
