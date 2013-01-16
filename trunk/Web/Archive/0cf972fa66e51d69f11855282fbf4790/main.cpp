#include <memory>
#include <iostream>

template < typename T, typename TDx = std::default_delete< T > >
class my_unique : private std::unique_ptr<T, TDx> {
public:
    using parent_type  = std::unique_ptr<T, TDx>;
    using pointer      = typename parent_type::pointer;
    using element_type = typename parent_type::element_type;
    using deleter_type = typename parent_type::deleter_type;
    
private:
    class ptrptr {     
        friend my_unique;
        my_unique* p;
        pointer a;
        ptrptr ( my_unique* parent ) : p(parent), a(parent->release()) {}
        ptrptr(const ptrptr& nocopy) = delete;
        ptrptr& operator=(const ptrptr& nocopy) = delete;
    public:
        ptrptr(ptrptr&& mover) = default;
        ptrptr& operator=(ptrptr&& mover) = default;
        operator pointer*() {return &a;}           
        ~ptrptr () {p->reset(a);}
    };
    
public:
    my_unique () : parent_type() {}
    my_unique (pointer p) : parent_type(p) {}
    my_unique (pointer p, const deleter_type& d) : parent_type(p, d) {}
    my_unique (pointer p, deleter_type&& d) : parent_type(p, std::move(d)) {}
    my_unique (std::nullptr_t p) : parent_type(p) {}
    my_unique (my_unique&& rhs) : parent_type( std::move(rhs) ) {}
    using parent_type::get;
    using parent_type::reset;
    using parent_type::release;
    using parent_type::swap;
    using parent_type::get_deleter;
    using parent_type::operator*;
    using parent_type::operator->;
    using parent_type::operator=;
    using parent_type::operator bool;
    ptrptr get_ptrptr() {return ptrptr(this);}
    
};

void FuckingCOM ( int** cominitializegogo ) {delete *cominitializegogo; *cominitializegogo = new int(48);}

int main () {    
    my_unique<int> meow( new int(24) );    
    FuckingCOM ( meow.get_ptrptr() );    
    std::cout << *meow << std::endl;
}