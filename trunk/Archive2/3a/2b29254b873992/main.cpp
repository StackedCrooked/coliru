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

#include <dlfcn.h>

void call(const char *symbol, const char *filename) {
    void (*func)();

    auto handle = dlopen(filename, RTLD_LAZY);
    *(void**)(&func) = dlsym(handle, symbol);
    func();
    dlclose(handle);
}

int main() {
    call("print", "./libA.a");
    call("print", "./libB.a");
}

#endif