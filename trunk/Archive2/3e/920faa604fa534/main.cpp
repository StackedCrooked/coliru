#include <iostream>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

//------------------------------------------------------------------------------
struct unused
{
    template<class T>
    unused(T&) {}
};

template<class T>
struct Getter
{
    typedef T* result_type;
    
    T* operator()(T& v) const
    {
        return &v;
    }

    T* operator()(unused) const
    {
        return nullptr;
    }
};

template<class U, class T>
U* poly_get(T* v)
{
    return boost::apply_visitor(Getter<U>(), *v);
}
//------------------------------------------------------------------------------

struct O{
};
struct A:O{
};
struct B:O{
};


int main(int argc, char** argv) {
    boost::variant<A, B> v;
    std::cout << "boost::get-------------------------------\n";
    std::cout << boost::get<O>(&v) << std::endl;
    std::cout << boost::get<A>(&v) << std::endl;
    std::cout << boost::get<B>(&v) << std::endl;
    std::cout << "poly_get---------------------------------\n";
    std::cout << poly_get<O>(&v) << std::endl;
    std::cout << poly_get<A>(&v) << std::endl;
    std::cout << poly_get<B>(&v) << std::endl;
    return 0;
}