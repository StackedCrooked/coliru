#ifdef A
#include <iostream>
extern "C" void print() {
    std::cout << "Hello from A!\n";
}
#endif

#ifdef B
#include <iostream>
extern "C" void print() {
    std::cout << "Hello from B!\n";
}
#endif

#ifdef MAIN

#include <utility>
#include <dlfcn.h>

template<typename... Args>
void call(const char *symbol, const char *filename, Args&&... args) {
    void (*func)(Args...);

    auto handle = dlopen(filename, RTLD_LAZY);
    *(void**)(&func) = dlsym(handle, symbol);
    func(std::forward<Args>(args)...);
    dlclose(handle);
}

int main() {
    call("print", "./libA.a");
    call("print", "./libB.a");
}

#endif