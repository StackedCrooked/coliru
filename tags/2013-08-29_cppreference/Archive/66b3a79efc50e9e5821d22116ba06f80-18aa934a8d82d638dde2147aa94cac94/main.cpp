#include <memory>

template <class T>
inline
T*
to_raw_pointer(T* p) noexcept
{
    return p;
}

template <class Pointer>
inline
typename std::pointer_traits<Pointer>::element_type*  //why can't this be ::pointer, which after all is T*???
to_raw_pointer(Pointer p) noexcept
{
    return ::to_raw_pointer(p.operator->());
}

int main()
{
    std::shared_ptr<int> p1(new int(1));
    int* r1 = to_raw_pointer(p1); 
    int* p2 = new int(2);
    int* r2 = to_raw_pointer(p2);
}