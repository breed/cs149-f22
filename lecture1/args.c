//
// Created by bcr33d on 8/22/22.
//

#include <stdio.h>

int main(int argc, char **argv) {
    printf("got %d arguments\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("arg %d %s\n", i, argv[i]);
    }
}
