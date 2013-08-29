#include <memory>
#include <iostream>


template< typename T, typename D>
class ptrptr_type {
    using parent_type  = std::unique_ptr<T, D>;
    using pointer      = typename parent_type::pointer;
    
    parent_type* p;
    pointer a;
    ptrptr_type(const ptrptr_type& nocopy) = delete;
    ptrptr_type& operator=(const ptrptr_type& nocopy) = delete;
public:
    ptrptr_type (std::unique_ptr<T, D>& ptr) : p(&ptr), a(ptr.release()) {}
    ptrptr_type(ptrptr_type&& mover) {p = mover.p; a = mover.a; mover.p = nullptr;}
    ptrptr_type& operator=(ptrptr_type&& mover) {p = mover.p; a = mover.a; mover.p = nullptr; return *this;}
    operator pointer*() {return &a;}           
    ~ptrptr_type () {if (p) p->reset(a);}
};
template< typename T, typename D>
ptrptr_type<T,D> ptrptr(std::unique_ptr<T, D>& ptr) {return ptrptr_type<T, D>(ptr);}

void FuckingCOM ( int** cominitializegogo ) {delete *cominitializegogo; *cominitializegogo = new int(48);}

int main () {    
    std::unique_ptr<int> meow( new int(24) );    
    FuckingCOM ( ptrptr(meow) );    
    std::cout << *meow << std::endl;
}