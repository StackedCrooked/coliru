#include <time.h>
#include <stdio.h>

#define LOG(fmt, ...) do {                                      \
    struct timespec t;                                          \
    clock_gettime(CLOCK_MONOTONIC, &t);                         \
    fprintf(stderr, "[%6ld.%06ld] ", t.tv_sec, t.tv_nsec/1000); \
    fprintf(stderr, fmt, ##__VA_ARGS__);                        \
    fprintf(stderr, "\n");                                      \
} while (0)

int main (int argc, char* argv[])
{
    int i;

    if (argc)
        LOG("argc != 0 (actually %d)", argc);
    else
        LOG("argc is zero!");

    if (argc > 1) {
        LOG("argc > 1");
        LOG("%s", argv[0]);
    }

    for (i = 0; i < argc; i++) {
        LOG("argv[%d] = \"%s\"", i, argv[i]);
    }

    return 0;
}