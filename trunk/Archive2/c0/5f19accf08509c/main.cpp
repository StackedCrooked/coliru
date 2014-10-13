#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) {
    switch(tflag) {
        case FTW_D:
        case FTW_DP: 
        case FTW_NS:
        case FTW_SL:
        case FTW_SLN:
        case FTW_DNR:
            break;
        case FTW_F: 
            if (sb->st_size > 20000)
                printf("%lu\t%s\n", sb->st_size, fpath);
            break;
    }
    return 0; /* To tell nftw() to continue */
}

int main(int argc, char *argv[]) {
    if (nftw((argc < 2) ? "." : argv[1], display_info, 20, FTW_DEPTH | FTW_MOUNT | FTW_PHYS) == -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }
}
