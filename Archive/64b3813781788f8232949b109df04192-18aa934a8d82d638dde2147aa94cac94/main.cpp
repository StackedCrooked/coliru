#include <memory>

template<class allocator>
struct alloc_aware {
    typedef typename allocator::size_type size_type;
    allocator* a;    
    size_type s;
    alloc_aware(allocator& alloc, size_type size):a(&alloc), s(size) {}
    template<class T> void operator()(T* ptr) {a->destroy(ptr); a->deallocate(ptr, s);}
};

template<class allocator>
struct only_deallocate {
    typedef typename allocator::size_type size_type;
    allocator* a;    
    size_type s;
    only_deallocate(allocator& alloc, size_type size):a(&alloc), s(size) {}
    template<class T> void operator()(T* ptr) {a->deallocate(ptr, s);}
    operator alloc_aware<allocator>() const {return alloc_aware<allocator>(*a, s);}
};
template<class node, class allocator, class... value_types>
std::unique_ptr<node,alloc_aware<allocator>> allocate_new_node(allocator& alloc, value_types&&... values) {
    std::unique_ptr<node, only_deallocate<allocator>> buf(alloc.allocate(sizeof(node)),{alloc, sizeof(node)});//allocate memory
    alloc.construct(buf.get(), std::forward<value_types>(values)...);
    return std::unique_ptr<node,alloc_aware<allocator>>(std::move(buf));
}

struct node {
    node(int) {}
};

int main() {
    std::allocator<node> alloc;
    auto r = allocate_new_node<node>(alloc, 3);
}