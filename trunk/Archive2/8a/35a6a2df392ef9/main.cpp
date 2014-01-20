#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    int out = open("cout.log", O_RDWR|O_CREAT|O_APPEND, 0600);
    if (-1 == out) { perror("opening cout.log"); return 255; }

    int save_out = dup(fileno(stdout));
    int save_err = dup(fileno(stderr));

    if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
    if (-1 == dup2(out, fileno(stderr))) { perror("cannot redirect stderr"); return 255; }

    fputs("doing an ls or something now", stderr);

    fflush(stdout); close(out);

    dup2(save_out, fileno(stdout));
    dup2(save_err, fileno(stderr));

    close(save_out);
    close(save_err);

    fputs("back to normal output", stderr);

    return 0;
}
