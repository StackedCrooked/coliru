#include <vector>

template<typename T, typename Allocator = std::allocator<T>>
struct A {
    A(typename std::vector<T, Allocator>::size_type count, const T& value, const Allocator& alloc = Allocator())
    : vect(count, value, alloc) {}
    template<class InputIt>
    A(InputIt first, InputIt last, const Allocator& alloc = Allocator());
    //: vect(first, last, alloc) {}
    
    std::vector<T, Allocator> vect;
};
    

int main() {
    A<int> a(42, 1);
}