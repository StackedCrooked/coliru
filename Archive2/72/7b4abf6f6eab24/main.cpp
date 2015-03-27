#include <boost/variant.hpp>
#include <boost/container/static_vector.hpp>
#include <vector>
#include <iostream>

template<typename T, int N> struct VectorAllocator {
    template<class U> struct rebind { typedef VectorAllocator<U, N> other; };
    typedef T value_type;
    int* allocate(int n, const void* hint);
    int* allocate(int n);
    void deallocate(int* p, int size);
};
template<typename T, int N> struct Vector : std::vector<T, VectorAllocator<T, N>> {
    static_assert(std::is_base_of<VectorAllocator<T, N>, std::vector<T, VectorAllocator<T, N>>>::value, "stdlib did not apply EBO!");
    typename std::aligned_storage<sizeof(T), alignof(T)>::type storage[N];
    bool sbo_used = false;
};
template<typename T, int N> int* VectorAllocator<T, N>::allocate(int n) {
    return allocate(n, nullptr);
}
template<typename T, int N> int* VectorAllocator<T, N>::allocate(int n, const void* hint) {
    auto self = static_cast<Vector<T, N>*>(this);
    if (n <= N && !self->sbo_used) {
        self->sbo_used = true;
        return &self->storage[0];
    }
    return (int*)malloc(n * sizeof(T));
}
template<typename T, int N> void VectorAllocator<T, N>::deallocate(int* p, int hint) {
    auto self = static_cast<Vector<T, N>*>(this);
    if (p == &self->storage[0]) {
        self->sbo_used = false;
        return;
    }
    free(p);
}


int main()
{
    Vector<int, 12> vec;
    for (int i = 1; i <= 20; ++i)
    {
        vec.push_back(i);

        for (auto i = 0 * vec.size(); i != vec.size(); ++i)
        {
            std::cout << vec[i] << ' ';
        }
        std::cout << std::endl;
    }
}
