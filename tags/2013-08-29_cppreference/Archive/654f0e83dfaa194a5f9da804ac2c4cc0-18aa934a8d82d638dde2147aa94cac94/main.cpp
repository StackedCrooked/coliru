#include <cassert>
#include <memory>
#include <cstdint>
#include <cstddef>
#include <cstdlib>

constexpr size_t G0_SIMD_ALIGN = 32;
// **** modified Brett's code here
static inline void *G0_SIMD_malloc (size_t size)
{
    constexpr size_t align = G0_SIMD_ALIGN;
    void *ptr, *uptr;

    static_assert(G0_SIMD_ALIGN >= sizeof(void *),
                  "insufficient alignment for pointer storage");

    static_assert((G0_SIMD_ALIGN & (G0_SIMD_ALIGN - 1)) == 0,
                  "G0_SIMD_ALIGN value must be a power of (2)");

    size += align; // raw pointer storage with alignment padding.

    if ((uptr = malloc(size)) == nullptr)
        return nullptr;

    size_t addr = reinterpret_cast<uintptr_t>(uptr);

    ptr = reinterpret_cast<void *>
        ((addr + align) & ~(align - 1));

    *(reinterpret_cast<void **>(ptr) - 1) = uptr; // (raw ptr)

    return ptr;
}

static inline void G0_SIMD_free (void *ptr)
{
    if (ptr != nullptr)
        free(*(reinterpret_cast<void **>(ptr) - 1)); // (raw ptr)
}
// **** end of modified Brett's code

template <typename T>
class simd_allocator {
public:
    using allocator_type = simd_allocator<T>;
    using value_type = T;

    T* allocate(size_t n) { return static_cast<T*>(G0_SIMD_malloc(n * sizeof(T))); }

    void deallocate(T* p, size_t) { G0_SIMD_free(p); }
};

#include <vector>

template <typename T>
using simd_vector = std::vector<T, simd_allocator<T>>;

int main() {
    simd_vector<float> v(100);
    v[3] = 4;
    assert(reinterpret_cast<uintptr_t>(v.data()) % 32 == 0);
}