#include <pthread.h>
#include <stdio.h>

int counter = 0;
pthread_mutex_t mutex;

void inc(int i)
{
    printf("inc called with %d\n", i);
    if (i == 0) return;
    printf("locking\n");
    pthread_mutex_lock(&mutex);
    counter++;
    inc(i-1);
    printf("unlocking\n");
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    //pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    //pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
    pthread_mutex_init(&mutex, &attr);
    inc(3);
    printf("%d\n", counter);
}
