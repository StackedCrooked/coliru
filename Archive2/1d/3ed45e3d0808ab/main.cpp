template<typename Guard, typename Lock, typename Func>
auto with(Lock lock, Func func) {
    Guard guard(lock);
    return func(guard);
}

#include <iostream>
#include <memory>
#include <cstdio>

struct FileCloser { void operator()(FILE* f) const noexcept { std::fclose(f); } };
using FilePtr = std::unique_ptr<FILE, FileCloser>;
using CharBuffer = std::unique_ptr<char[]>;

int main() {
    with<FilePtr>(std::fopen("data.txt", "w"), [](FilePtr& fp) {
        std::fputs("This is some data\n", &*fp);
    });

    with<FilePtr>(std::fopen("data.txt", "r"), [](FilePtr& fp) {
        with<CharBuffer>(new char[24], [&](CharBuffer& buf) {
            if(char* p = std::fgets(&buf[0], 24, &*fp)) {
                std::cout << p;
            } else {
                std::cout << "No data :(\n";
            }
        });
    });
}