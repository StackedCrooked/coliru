#include <initializer_list>
#include <vector>
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <memory>

typedef unsigned char b8;

template <typename _Tp>
class initializer_list_generator : public std::initializer_list<_Tp> {
private:
    std::shared_ptr<_Tp> smem;

public:
    initializer_list_generator(std::initializer_list<_Tp>& generated, _Tp* mem) :
        std::initializer_list<_Tp>(generated),
        smem(mem)
    {}
};

template <typename _Tp, typename _IteratorType>
initializer_list_generator<_Tp> 
hack_create_ilist(_IteratorType start, _IteratorType end) 
{
    typedef unsigned char b8;
    
    std::initializer_list<_Tp> out;
    b8* raw = reinterpret_cast<b8*>(&out);
    
    _Tp*& dptr = *(_Tp**)raw;
    delete[] dptr;

    size_t distance = std::distance(start, end);
    *(size_t*)(raw + 8) = distance;

    _Tp* mem = new _Tp[distance];
    _Tp* pos = mem;
    for(auto s = start; s != end; ++s) {
        *(pos++) = *s;
    }
    dptr = mem;
    
    return initializer_list_generator<_Tp>(out, mem);
}

void fn(std::initializer_list<int> d) {
    for(int i : d) {
        std::cout << i << std::endl;
    }
}

int main() {
    std::vector<int> x{1,2,3,4,5,6};
    initializer_list_generator<int> gen = hack_create_ilist<int>(x.begin(), x.end());
    std::initializer_list<int> ls = gen;
    fn(ls);
    
    //take that.
}