#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform_view.hpp>
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
};

struct nil {};
// end shit
/////////////////////////////////////////////////////////

struct wrap_ref_func {
    
    wrap_ref_func(lua_t& state) : state(state) {}
    lua_t& state;

    template <typename> struct result { typedef void type; };
    template <typename CFunction>
    void operator()(CFunction& f) const 
    { 
        state.register_function("foo", f);
    }
};

typedef mpl::vector<signed int, double, bool, std::string, nil> basic_types;

int main()
{
    using namespace boost::phoenix::arg_names;

    lua_t lua;
    phx::function<wrap_ref_func> register_function(lua);

    typedef mpl::transform_view<basic_types, c_funs::basic::void_binary_same<mpl::_> > bin_same_functions;
    mpl::for_each<bin_same_functions>(register_function(arg1));

    typedef mpl::transform_view<basic_types, c_funs::basic::void_unary<mpl::_> > unary_functions;;
    mpl::for_each<unary_functions>(register_function(arg1));
}

