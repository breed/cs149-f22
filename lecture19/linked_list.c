#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int i;
    pthread_mutex_t mutex;
    struct node *next;
};

struct node *head;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int add(int i)
{
    struct node **prev = &head;

    // walk the list keeping track of the previous next pointer
    for (struct node *current = *prev; current; current = current->next) {
        if (current->i == i) {
            return 0;
        }
        prev = &current->next;
    }

    // add the node
    struct node *new_node = malloc(sizeof *new_node);
    new_node->i = i;
    new_node->next = NULL;
    *prev = new_node;
    return 1;
}

int main()
{
    for (int i = 0; i < 50000; i++) {
        add(i);
    }

    int count = 0;
    struct node *ptr = head;
    while (ptr) {
        count++;
        ptr = ptr->next;
    }
    printf("%d\n", count);
}
