#include <memory>

template <class T>
inline T* to_raw_pointer(T* p) noexcept
{return p;}

template <class T>
inline auto to_raw_pointer(T& p) noexcept -> decltype(to_raw_pointer(p.operator->()))
{return to_raw_pointer(p.operator->());}


std::unique_ptr<int> rval() {return std::unique_ptr<int>{};}

int main()
{
    std::shared_ptr<int> p1(new int(1));
    int* r1 = to_raw_pointer(p1); 
    int* p2 = new int(2);
    int* r2 = to_raw_pointer(p2);
    const std::shared_ptr<int> p3(new int(1));
    const int* r3 = to_raw_pointer(p3); 
    const std::shared_ptr<int> p4(new int(1));
    const int* r4 = to_raw_pointer(p4); 
    std::unique_ptr<int> p5(new int(1));
    int* r5 = to_raw_pointer(p5); 
    const std::unique_ptr<int> p6(new int(1));
    int* r6 = to_raw_pointer(p6); 
    //int* r7 = to_raw_pointer(rval()); //correctly gives compiler error
    const int* p8 = new int(2);
    const int* r8 = to_raw_pointer(p7);
}