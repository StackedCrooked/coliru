#include <iostream>
#include <memory>

struct Tracked {
    Tracked() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    Tracked(const Tracked&) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    Tracked(Tracked&&) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    template<typename T>
    Tracked(T&&) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    ~Tracked() { std::cout << __PRETTY_FUNCTION__ << '\n'; }

    Tracked& operator=(const Tracked&) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return *this;
    }
    Tracked& operator=(Tracked&&) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return *this;
    }
};

template<typename T>
struct MyAllocator {
    MyAllocator() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    MyAllocator(const MyAllocator&) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    MyAllocator(MyAllocator&&) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    template<typename U>
    MyAllocator(const MyAllocator<U>&) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    template<typename U>
    MyAllocator(MyAllocator<U>&&) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
    ~MyAllocator() { std::cout << __PRETTY_FUNCTION__ << '\n'; }

    MyAllocator& operator=(const MyAllocator&) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return *this;
    }
    MyAllocator& operator=(MyAllocator&&) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return *this;
    }

    using value_type = T;

    T* allocate(size_t n) {
        std::cout << __PRETTY_FUNCTION__ << " (" << n << ")\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* ptr, size_t n) {
        std::cout << __PRETTY_FUNCTION__ << " (" << static_cast<const void*>(ptr) << ", " << n << ")\n";
        ::operator delete(ptr);
    }

    template<typename... Args>
    void construct(T* ptr, Args&&... args) {
        std::cout << __PRETTY_FUNCTION__ << " (" << static_cast<const void*>(ptr) << ", ...)\n";
        new(static_cast<void*>(ptr)) T(std::forward<Args>(args)...);
    }

    void destroy(T* ptr) {
        std::cout << __PRETTY_FUNCTION__ << " (" << static_cast<const void*>(ptr) << ")\n";
        ptr->~T();
    }

    template<typename U>
    struct rebind {
        using other = MyAllocator<U>;
    };
};

int main() {
    auto p = std::allocate_shared<Tracked>(MyAllocator<Tracked>{});
}