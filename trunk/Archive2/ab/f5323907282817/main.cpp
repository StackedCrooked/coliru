#include <iostream>
#include <vector>

//////////////////////////////////////////////////////////////////////
class arena
{
    unsigned char * data;
    std::size_t offset;

 public:
    explicit arena(size_t n)
      : data(static_cast<unsigned char *>(::operator new(n))), offset(0) { }

    arena(arena const &) = delete;

    arena & operator = (arena const &) = delete;

    ~arena() { ::operator delete(data); }

    void * allocate(std::size_t, std::size_t)
    {
        if (offset) throw std::bad_alloc();

        ++offset;
        return data;
    }

    void deallocate(void *, std::size_t) { offset = 0; }
};

//////////////////////////////////////////////////////////////////////
template <typename T>
class arena_allocator
{
    arena * my_arena;

 public:
    template <typename U> friend class arena_allocator;
    using value_type = T;
    using pointer = T *;
    using propagate_on_container_copy_assignment = std::false_type;
    using propagate_on_container_move_assignment = std::false_type;
    using propagate_on_container_swap = std::false_type;

    explicit arena_allocator(arena * a) : my_arena(a) { }

    arena_allocator(arena_allocator const & rhs) : my_arena(rhs.my_arena) { }

    pointer allocate(std::size_t n)
    {
        return static_cast<pointer>(
		         my_arena->allocate(n * sizeof(T), alignof(T)));
    }

    void deallocate(pointer p, std::size_t n)
    	{ my_arena->deallocate(p, n * sizeof(T)); }

	template <typename U>
    bool operator == (arena_allocator<U> const &) const { return false; }

	template <typename U>
    bool operator != (arena_allocator<U> const &) const { return true; }

};


int main(void)
{
    arena a(1024);
    arena_allocator<int> aa{&a};

    std::vector<int, arena_allocator<int>> v{aa};
    
    for (auto i : { 1,2,3,4,5,6,7,8,9 })
        v.push_back(i);

}
