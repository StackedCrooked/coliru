#include <vector>
#include <cstddef>

namespace detail {
    template<typename T, typename Derived> struct derived_allocator {
        T* allocate(std::size_t n) {
            return static_cast<Derived*>(this)->allocate(n);
        }
        void deallocate(T* p) {
            return static_cast<Derived*>(this)->deallocate(p);
        }
    };
}
template<typename T, std::size_t N> struct small_vector : std::vector<T, detail::derived_allocator<T, small_vector<T, N>>> {
    typename std::aligned_storage<sizeof(T), alignof(T)>::type storage[N];
    bool used = false;
    
    T* allocate(std::size_t n) {
        if (used) return new char[n];
        return (T*)&storage[0];
    }
    void deallocate(T* p) {
        if (p == (T*)&storage[0]) return;
        delete[] p;
    }
    
    small_vector() {
        reserve(N);
    }
    
    using std::vector::vector;
};