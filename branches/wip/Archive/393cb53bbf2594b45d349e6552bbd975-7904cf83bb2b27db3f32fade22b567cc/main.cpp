#include <boost/blank.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits.hpp>
#include <boost/variant.hpp>
#include <iostream>

using namespace boost;
using namespace boost::mpl;
using namespace std;

struct NoThrow
{
    NoThrow() throw() { }
    NoThrow(NoThrow const &) throw() { }
};

int g_called = 0;
struct Throw
{
    Throw() { if (2 < ++g_called) throw 1; }
    Throw(Throw const &) { if (2 < ++g_called) throw 1; }
};

int main() 
{
    BOOST_MPL_ASSERT((has_nothrow_constructor<blank>));
    BOOST_MPL_ASSERT((has_nothrow_constructor<NoThrow>));
    BOOST_MPL_ASSERT((not_<has_nothrow_constructor<Throw> >));

    typedef variant<blank, Throw, NoThrow> Variant;
    auto v = Variant();
    cout << v.type().name() << endl;
    v = NoThrow();
    cout << v.type().name() << endl;
    try
    {
        v = Throw();
        cout << "unreachable" << endl;
    }
    catch (...)
    {
        cout << v.type().name() << endl;
    }
    
    return 0;
}
