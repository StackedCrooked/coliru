#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char * weisheiten[] = {
    "Wochenende",
    "Saufen",
    "Geil",
    "Diese ganze Fickscheißarbeit",
    "Ich dreh durch",
    "Scheiß Arbeit",
};

const double F = 1.0 / (RAND_MAX + 1.0);

int random_number(int bound)
{
    return (int)(rand() * F * bound);
}

int main()
{
    srand(time(0));
    for (int i = 0; i < 10; ++i)
    {
        printf("%s!\n", weisheiten[random_number(6)]);
    }
}
