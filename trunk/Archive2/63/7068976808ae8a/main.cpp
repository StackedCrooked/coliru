#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    auto handle_deleter = [] (int* handle) {
        close(handle);
    };
    
    std::unique_ptr<int, handle_deleter> uptr
        { open("main.cpp") };
}
