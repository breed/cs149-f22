//
// Created by bcr33d on 8/22/22.
//
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *this_is_one = "123.5\0abcd";
    char *end;
    int num = strtol(this_is_one, &end, 10);
    num += 2;
    printf("%s %d %d\n", this_is_one, num, (int)*end);
}
