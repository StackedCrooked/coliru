#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void prepend(const char* fname, char const* prepend_data, size_t n)
{
    struct stat s;
    stat(fname, &s);
    size_t size    = s.st_size;
    size_t resized = size + n;

    truncate(fname, resized);
    int fd = open(fname, O_RDWR);
    char* mapped_file = (void*) mmap(NULL, resized, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    memmove(mapped_file + n, mapped_file, size);
    memcpy (mapped_file, prepend_data, n);
}

int main() {
    char const to_prepend[] = { 1,2,3,4,5,6 };
    prepend("data.dat", to_prepend, sizeof to_prepend);
    return 0;
}
