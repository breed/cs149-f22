#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <threads.h>

static thread_local volatile int counter = 0;

// mythread()
//
// Simply adds 1 to counter repeatedly, in a loop
// No, this is not how you would add 10,000,000 to
// a counter, but it shows the problem nicely.
//
void *mythread(void *arg) {
    printf("%s: begin\n", (char *) arg);
    int i;
    if (strcmp(arg, "A") == 0) counter++;
    for (i = 0; i < 1e7; i++) {
        counter++;
    //    counter = counter + 1;
    }
    printf("%s: done %d\n", (char *) arg, counter);
    return NULL;
}

// main()
//
// Just launches two threads (pthread_create)
// and then waits for them (pthread_join)
//
int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    printf("main: begin (counter = %d)\n", counter);

    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");

    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

//    mythread("A");
    //mythread("B");
    printf("main: done with both (counter = %d)\n", counter);
    return 0;
}
