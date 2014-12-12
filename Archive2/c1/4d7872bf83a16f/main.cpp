// For open
#include <sys/stat.h>
#include <fcntl.h>

// For close
#include <unistd.h>

// For unique_ptr
#include <memory>

struct posix_close
{
    using pointer = int;
    void operator()(pointer fd)
    {
        close(fd);
    }
};

int
main()
{
    std::unique_ptr<int, posix_close> p(open("testing", O_CREAT));
    int fd = p.get();
}