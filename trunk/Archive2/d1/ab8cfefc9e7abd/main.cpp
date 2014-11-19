#include <algorithm>
#include <iostream>

// for mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

const char* map_file(const char* fname, size_t& length);

int main()
{
    size_t length;
    const char* f = map_file("main.cpp", length);
    const char* l = f + length;

    uintmax_t m_numLines = 0;
    const char * lineStart = f;
    const char * lineEnd = 0;
    while (f && f!=l)
    {        
        if ((f = static_cast<const char*>(memchr(f, '\n', l-f))))
        {
            m_numLines++;
            lineEnd = f;
            
            std::string line(lineStart,lineEnd);
            
            lineStart = lineEnd + 1;
            f++;    
            
            std::cout << "Line " << m_numLines << ": " << line << std::endl;
        }
        
        
    }

    //std::cout << f << std::endl;
    std::cout << "m_numLines = " << m_numLines << "\n";
}

void handle_error(const char* msg) {
    perror(msg); 
    exit(255);
}

const char* map_file(const char* fname, size_t& length)
{
    int fd = open(fname, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    posix_fadvise(fd, 0, 0, 1);  // FDADVICE_SEQUENTIAL

    // obtain file size
    struct stat sb;
    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    length = sb.st_size;

    const char* addr = static_cast<const char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
    if (addr == MAP_FAILED)
        handle_error("mmap");

    // TODO close fd at some point in time, call munmap(...)
    return addr;
}
