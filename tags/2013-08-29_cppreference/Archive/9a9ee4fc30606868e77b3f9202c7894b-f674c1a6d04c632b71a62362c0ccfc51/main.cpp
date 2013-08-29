#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <iostream>

namespace phx = boost::phoenix;
namespace mpl = boost::mpl;

/////////////////////////////////////////////////////////
// plumbing added just to make it compile...
// this is "your shit" :)
namespace c_funs { namespace basic {
    template <typename> struct void_unary { };
    template <typename> struct void_binary_same { };
    template <typename, typename> struct void_binary_diff { };
} }

struct lua_t 
{ 
    static constexpr struct Nil {} nil = {};
    template <typename CF> void register_function(std::string const& n, CF&) const 
    {
        std::cout << "ACK: lua_t::register_function(\"" << n << "\", " << typeid(CF).name() << ")\n";
    }
} lua;

struct nil {};
// end shit
/////////////////////////////////////////////////////////

struct wrap_ref_func {
    template <typename> struct result { typedef void type; };
    template <typename CFunction>
    void operator()(CFunction& f) const 
    { 
        lua.register_function("foo", f);
    }
};

int main()
{
    using namespace boost::phoenix::arg_names;

    phx::function<wrap_ref_func> register_function;

    typedef mpl::vector<signed int, double, bool, std::string, nil> basic_types;
    mpl::for_each<basic_types>(register_function(arg1));
}
