#include <boost/typeof/typeof.hpp>

template<int N> struct SomeTemplate
{
        enum {n = N};
        int SomeMember;
};

int main() {
        SomeTemplate<-5> foo;
        typedef BOOST_TYPEOF(foo) t;
        SomeTemplate<t::n> bar;
        return 0;
}