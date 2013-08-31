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
    template <typename T> using void_unary = void(*)(T);
    template <typename T> using void_binary_same = void(*)(T, T);
    template <typename T, typename U> using void_binary_diff = void(*)(T, U);
} }

struct lua_t 
{ 
    static constexpr struct Nil {} nil = {};
    template <typename CF> void register_function(std::string const& n, CF) const 
    {
        std::cout << "ACK: lua_t::register_function(\"" << n << "\", " << typeid(CF).name() << ")\n";
    }
};

struct nil {};
// end shit
/////////////////////////////////////////////////////////

template <template<typename...> class Alias>
struct wrap_ref_func {
    
    wrap_ref_func(lua_t& state) : state(state) {}
    lua_t& state;

    template <typename...> struct result { typedef void type; };
    template <typename... Arg>
    void operator()(Arg const&... f) const 
    { 
        state.register_function("foo", Alias<Arg...>());
    }
};

typedef mpl::vector<signed int, double, bool, std::string, nil> basic_types;

int main()
{
    using namespace boost::phoenix::arg_names;

    lua_t lua;
    phx::function<wrap_ref_func<c_funs::basic::void_binary_same> > reg_bin_same(lua);
    mpl::for_each<basic_types>(reg_bin_same(arg1));

    phx::function<wrap_ref_func<c_funs::basic::void_unary> > reg_unary(lua);
    mpl::for_each<basic_types>(reg_unary(arg1));
}

