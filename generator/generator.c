#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TIMES 10000

int main(void)
{
    int cmd;
    srand((unsigned)time(NULL));
    int i;
    for (i = 0; i < TIMES; i++) {
        cmd = rand()%2;
        printf("%d\n%d\n", cmd, rand() % 20);
    }
    return 0;
}