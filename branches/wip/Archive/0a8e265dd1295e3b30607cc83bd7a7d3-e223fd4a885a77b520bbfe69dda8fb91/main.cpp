#include <algorithm>
#include <iostream>

// for mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

void handle_error(const char* msg) {
    perror(msg); 
    exit(255);
}

const char* map_file(const char* fname, size_t& length)
{
    int fd = open(fname, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    // obtain file size
    struct stat sb;
    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    length = sb.st_size;

    const char* addr = static_cast<const char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
    if (addr == MAP_FAILED)
        handle_error("mmap");

    return addr;
}

int main()
{
    size_t length;
    auto f = map_file("main.cpp", length);
    auto l = f + length;

    size_t m_numLines = std::count(f, l, '\n');

    std::cout << "m_numLines = " << (m_numLines+1) << "\n";
}
