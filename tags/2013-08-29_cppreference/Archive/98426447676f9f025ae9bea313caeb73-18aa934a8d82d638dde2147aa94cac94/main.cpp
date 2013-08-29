#include <memory>


template <class T>
inline auto to_raw_pointer(T& p) noexcept -> decltype(p.get())
{return p.get();}

template <class T>
inline T* to_raw_pointer(T* p) noexcept
{return p;}

int main()
{
    std::shared_ptr<int> p1(new int(1));
    int* r1 = to_raw_pointer(p1); 
    int* p2 = new int(2);
    int* r2 = to_raw_pointer(p2);
}