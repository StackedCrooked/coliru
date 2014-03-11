#include <boost/phoenix/phoenix.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/bind.hpp>
#include <string>
#include <vector>
#include <algorithm>

using namespace boost::phoenix::arg_names;
namespace phx = boost::phoenix;

template <typename Accessor>
struct compare_by_impl {
    compare_by_impl(Accessor f) : _f(f) {}

    template <typename, typename> struct result { typedef bool type; };

    template <typename T, typename U>
    bool operator()(T const& a, U const& b) const {
        return _f(a) < _f(b);
    }
  private:
    Accessor _f;
};

template <typename Accessor>
compare_by_impl<typename boost::remove_reference<Accessor>::type> comparer_by(Accessor const& f) {
    return compare_by_impl<typename boost::remove_reference<Accessor>::type>(f);
}

// In a header
struct foo
{
   char * a;
   char * c_str() { return a; }
};

// In a header
struct bar
{
    foo * X;          

    bar(foo * _X) : X(_X) {}
    bool operator < (const bar& rhs) const
    {
        return std::string(X->c_str()) < std::string(rhs.X->c_str());
    }
};

struct bars : public std::vector<bar> {/* ... some stuff  */};

// Some other header
bars Bs;

// A cpp file
//... other stuff happens that fills the Xs vector with objects

namespace /* filestatic*/ {
    // sadly C++03 didn't allow local structs as template arguments

    struct accessX_c_str {
        typedef const char* result_type;

        const char* operator()(bar const& b) const {
            return b.X->c_str();
        }
    };
}

void Function()
{
    std::sort(Bs.begin(), Bs.end(), comparer_by(accessX_c_str()));
    std::sort(Bs.begin(), Bs.end(), phx::bind(accessX_c_str(), arg1) < phx::bind(accessX_c_str(), arg2));

    std::sort(Bs.begin(), Bs.end(), comparer_by(phx::bind(&foo::c_str, phx::lambda [ phx::bind(&bar::X, arg1) ](arg1) ))); // this is where deduction is _very_ handy
    
    std::sort(Bs.begin(), Bs.end(), 
            phx::bind(&foo::c_str, phx::lambda [ phx::bind(&bar::X, arg1) ](arg1)) 
          < phx::bind(&foo::c_str, phx::lambda [ phx::bind(&bar::X, arg1) ](arg2))
        );
}

int main()
{
    Function();
}
