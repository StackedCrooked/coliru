#include <stdio.h>
enum {
    thing1 = 1,
    thing2 = 0,
    thing3 = 5,
    thing4 = 2
};

enum test_e {
    ay = 1,
    be = 2,
    se = 0,
    de = 3
};

int main()
{
    enum test_e test = ay;
    for (int i = 0; i < 2; i++) {
        printf("regular enum %d, %d\n", thing1, thing1 + 1);
        printf("typed enum %d, %d\n", test, test + 1);
        //test = test+1;
    }
    return 0;
}
