#include <algorithm>
#include <iostream>

#include <fcntl.h>  // O_RDONLY
#include <unistd.h> // read
#include <cstring>  // memchr

void handle_error(const char* msg)
{
    perror(msg);
    exit(255);
}

static uintmax_t wc(char const *fname)
{
    static const auto BUFFER_SIZE = 16*1024;
    int fd = open(fname, O_RDONLY);
    if(fd == -1)
        handle_error("open");

    /* Advise the kernel of our access pattern.  */
    posix_fadvise(fd, 0, 0, 1);  // FDADVICE_SEQUENTIAL

    char buf[BUFFER_SIZE + 1];
    uintmax_t lines = 0;

    while(size_t bytes_read = read(fd, buf, BUFFER_SIZE))
    {
        if(bytes_read == (size_t)-1)
            handle_error("read failed");
        if (!bytes_read)
            break;

        for(char *p = buf; (p = (char*) memchr(p, '\n', (buf + bytes_read) - p)); ++p)
            ++lines;
    }
    
    return lines;
}

int main()
{
    auto m_numLines = wc("main.cpp");
    std::cout << "m_numLines = " << m_numLines << "\n";
}
