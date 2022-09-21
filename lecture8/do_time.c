#include <stdio.h>
#include <time.h>

struct timings {
    struct timespec start;
    struct timespec end;
};

int main()
{
    struct timings t[10];
    for (int try = 0; try < 10; try++) {
        if (clock_gettime(CLOCK_REALTIME, &t[try].start) == -1) {
            perror("clock_gettime");
        }
        int x = 1000;
        int y = 3;
        for (int i = 0; i < 150000000; i++) {
            x = x % 2;
            y += x;
            x += y;
        }
        if (clock_gettime(CLOCK_REALTIME, &t[try].end) == -1) {
            perror("clock_gettime");
        }
        int duration = (t[try].end.tv_sec - t[try].start.tv_sec)*1000 +
                       (t[try].end.tv_nsec - t[try].start.tv_nsec)/1000000;
        printf("duration = %d ms\n", duration);
    }
}
