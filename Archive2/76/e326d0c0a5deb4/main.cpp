#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <memory>

int main()
{
    auto handle_deleter = [] (int* handle) {
        close(*handle);
    };
    
    std::unique_ptr<int, decltype(handle_deleter)> uptr
        { open("main.cpp", O_RDONLY) };
}
