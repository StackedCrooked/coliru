#include <iostream>
#include <vector>
#include <cassert>

class A
{
    std::vector< int > v_;
    mutable std::vector< int >::const_iterator current_;

public:
    A() : v_{1,2,3}, current_(v_.end()) {}
    
    int get() const // note the const
    {
        assert( !v_.empty() );
        if( current_ == v_.end() ) current_ = v_.begin();
        return *current_++;
    }
};

int main()
{
    const A a;
    std::cout << a.get() << std::endl;
    std::cout << a.get() << std::endl;
    std::cout << a.get() << std::endl;
    std::cout << a.get() << std::endl;
}