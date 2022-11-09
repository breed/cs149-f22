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
    pthread_mutex_t *current_mutex = &mutex;

    pthread_mutex_lock(current_mutex);
    // walk the list keeping track of the previous next pointer
    for (struct node *current = *prev; current; current = current->next) {
        if (current->i == i) {
            prev = NULL;
            break;
        }
        pthread_mutex_lock(&current->mutex);
        pthread_mutex_unlock(current_mutex);
        current_mutex = &current->mutex;
        prev = &current->next;
    }

    if (prev) {
        // add the node
        struct node *new_node = malloc(sizeof *new_node);
        new_node->i = i;
        new_node->next = NULL;
        *prev = new_node;
    }
    pthread_mutex_unlock(current_mutex);
    return prev ? 1 : 0;
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
