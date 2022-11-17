#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct person {
    char *name;
    int duration;
};

char *name[] = {
    "abe",
    "amy",
    "cal",
    "carrie",
    "terry",
    "berry",
    "sherry",
    "ben",
    "jen",
    "ken",
};

sem_t sem;

void *enter_club(void *v)
{
    struct person *p = v;
    sem_wait(&sem);
    printf("%s entered club\n", p->name);
    sleep(p->duration);
    printf("%s left club after %d seconds\n", p->name, p->duration);
    sem_post(&sem);
}

int main()
{
    pthread_t ph[10];
    struct person people[10];

    sem_init(&sem, 0, 0);
    for (int i = 0; i < 10; i++) {
        people[i].name = name[i];
        people[i].duration = i;
    }

    for (int i = 0; i < 10; i++) {
        pthread_create(&ph[i], NULL, enter_club, &people[i]);
    }

    for (int i = 0; i < 3; i++) {
        sleep(3);
        printf("--- letting 1 more in\n");
        sem_post(&sem);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(ph[i], NULL);
    }
}
