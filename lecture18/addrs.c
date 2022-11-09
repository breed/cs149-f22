#include <stdio.h>

int foo()
{
    int i = 0xd00d;
    int j = 0xdead;
    int k = 0xd00d;
    int l = 0xdead;
    int m = 0xd00d;
    int n = 0xdead;
    printf("%p %p %p %p %p %p\n", &i, &j, &k, &l, &m, &n);
}

void goo()
{
    char buffer[1];
    char *ptr1;
    char *ptr2;
    ptr2 = buffer;
    printf("ptr1 %p ptr2 %p buffer %p\n", ptr1, ptr2, buffer);
    printf("& ptr1 %p ptr2 %p buffer %p\n", &ptr1, &ptr2, &buffer);
}

int main(int argc, char **argv)
{
    foo();
    goo();
}
