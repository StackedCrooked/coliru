#include <iostream>
#include <memory>
#include <vector>

struct mytype {
    int value;
    
    mytype(int v) : value{v} {}
    
    operator int() const { return value; }
};

namespace std {
template <>
struct allocator<::mytype> {
    using value_type = mytype;

    constexpr allocator() = default;
    template <typename U>
    constexpr allocator(const allocator<U>&) {}
    
    mytype* allocate(std::size_t n) {
        auto result = ::operator new(n * sizeof(mytype));
        if (!result) throw bad_alloc();
        return static_cast<mytype*>(result);
    }
    
    void deallocate(mytype* ptr, std::size_t) noexcept {
        ::operator delete(ptr);
    }
    
    template <typename U, typename...Args>
    void construct(U* ptr, Args&&...args) {
        ::new ((void*)ptr) U(std::forward<Args>(args)...);
        std::cout << "constructed " << *ptr << '\n';
    }

    template <typename U>
    void destroy(U* ptr) noexcept {
        std::cout << "destroying " << *ptr << '\n';
        ptr->~U();
    }
    
    friend constexpr bool operator == (const allocator&, const allocator&) noexcept {
        return true;
    }
    friend constexpr bool operator != (const allocator&, const allocator&) noexcept {
        return false;
    }
};
} // namespace std

int main() {
    std::vector<mytype>{1,2,3};
}
