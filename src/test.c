#include "set.h"

#define TIMES 10000

int main(void)
{
    int i;
    PToMySet s;
    s = init();
    for (i = 0; i < TIMES; i++) {
        int cmd, num;
        scanf("%d%d", &cmd, &num);
        if (cmd) {
            insert(s, num);
            printf("insert %d\n", num);
            printf("now: ");
            print(s);
        } else {
            erase(s, num);
            printf("erase %d\n", num);
            printf("now: ");
            print(s);
        }
    }
    printf("finally: \n");
    print(s);

    delete(&s);
    return 0;
}