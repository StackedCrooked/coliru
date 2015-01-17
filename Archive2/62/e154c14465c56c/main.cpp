/////////////////////////////////////////////////////////////////////////////////
// we don't have c++11
namespace std {
    static const struct nullptr_t { template <typename T> operator T*() const { return static_cast<T*>(0); } } nullptr;
}

#include <boost/config.hpp>
#undef BOOST_NO_CXX11_NULLPTR // override the default
 
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <boost/type.hpp>

template<typename F>
struct OptionalDeleter {
    explicit OptionalDeleter(F const& f) : _f(f) {}

    template <typename T>
        void operator()(T arg) const { _f(arg); }

    void operator()(std::nullptr_t) const { std::cout << "Empty, not deleting\n"; }
  private:
    F _f;
};

template <typename F>
OptionalDeleter<F> make_optional_deleter(F const& f) { return OptionalDeleter<F>(f); }

#include <boost/phoenix.hpp>
using boost::phoenix::val;

int main() {
    BOOST_AUTO(d, make_optional_deleter(std::cout << val("deleting")));
    
    using namespace boost;
    {
        shared_ptr<int> empty(std::nullptr, d);
    } // deleter not called, empty

    {
        shared_ptr<int> thing(static_cast<int*>(0), d);
    } // deleter called, thing not empty
}
