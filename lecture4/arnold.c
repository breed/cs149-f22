#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *name = "arnold";
int dollars = 100;

int main()
{
    printf("i am %s\n", name);
    // i figure out if i'm the clone
    if (fork() == 0) {
        name = "arnold clone";
    } else {
        name = "the real arnold";
    }
    fork();
    sleep(1);
    printf("i am %s\n", name);
    sleep(1);
    printf("i, %s, have %d dollars\n", name, dollars);
    // spend 10 dollars
    dollars -= 10;
    sleep(1);
    printf("i, %s, have %d dollars\n", name, dollars);
}
