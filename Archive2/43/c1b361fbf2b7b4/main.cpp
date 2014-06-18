#include <cassert>
#include <cstdint>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <stdlib.h>

namespace { constexpr std::size_t desired_alignment = 32; }

void* operator new[](std::size_t size) {
    struct with_dtor { ~with_dtor() {} };
    static std::aligned_storage<sizeof(with_dtor), alignof(with_dtor)>::type dummy;

    static bool first_run = true;
    static bool detecting = true;
    static std::size_t extra = 0;
    if(first_run) {
        first_run = false;
        new with_dtor[1];
    } else if(detecting) {
        detecting = false;
        extra = size - sizeof(with_dtor);
        assert(extra <= desired_alignment);
        return &dummy;
    }
    
    void* ptr;
    int r = ::posix_memalign(&ptr, desired_alignment, size); // or just call the over-aligned operator new
    if(r != 0) throw std::bad_alloc();
    return static_cast<char*>(ptr) + (desired_alignment - extra);
}

void operator delete[](void* ptr) noexcept {
    //std::align still missing from GCC
    auto u = reinterpret_cast<std::uintptr_t>(ptr);
    void* aligned = reinterpret_cast<void*>(u - (u % desired_alignment));
    assert(aligned);
    ::free(aligned);
}

#include <iostream>
struct foo { ~foo() {} };
int main() {
    auto p = new int[10];
    std::cout << static_cast<void*>(p) << '\n';
    auto q = new foo[10];
    std::cout << static_cast<void*>(q) << '\n';
    delete[] p;
    delete[] q;
}
