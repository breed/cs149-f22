#include <stdio.h>

struct person {
    int age;
    char *name;
};

struct person people[] = {{20, "tim"}, {23, "amy"}, {35, "ann"}};

//int ages[] = { 20, 23, 35 };
//char *names[] = { "tim", "amy", "ann" };

void inc_age(struct person *p) {
    // (*p).age++;
    p->age++;
}

int main()
{
    inc_age(&people[0]);
    inc_age(&people[2]);
    for (int i = 0; i < 3; i++) {
        printf("%s: %d\n", people[i].name, people[i].age);
    }
}
