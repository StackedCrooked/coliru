#include <stdio.h>

struct user {
    const char *name;
    int age;
};

typedef struct user USER;

USER u1 = { "Dave", 78 };

USER uArray[4] = {
    { "Allan", 12 },
    { "Bob", 34 },
    { "Chris", 56 },
    u1
};

int main()
{
    int i;
    
    for (i = 0; i < 4; ++i)
    {
        printf("%s: %d\n", uArray[i].name, uArray[i].age);
    }
    return 0;
}