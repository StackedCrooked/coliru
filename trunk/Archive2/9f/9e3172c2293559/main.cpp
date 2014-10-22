#include <iostream>
#include <memory>
#include <vector>
#include <dlfcn.h>
#include <unistd.h>

using handle = std::unique_ptr<void, int(*)(void*)>;
inline handle get_library(const char* filename, int flags = RTLD_LAZY) {
    return handle{dlopen(filename, flags), &dlclose};
}
template<typename T = void>
inline T* get_symbol(const handle& ptr, const char* symbol) {
    return reinterpret_cast<T*>(dlsym(ptr.get(), symbol));
}

int main() {
    auto lib = get_library("./liblib.so");
    const auto count = *get_symbol<const std::size_t>(lib, "strings_length");
    auto list = get_symbol<const char*>(lib, "strings");

    std::vector<std::string> strings(list, list + count);
    for(auto& string : strings)
        std::cout << string << ' ';
    std::cout << '\n';
}
