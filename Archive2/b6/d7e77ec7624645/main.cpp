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
    compare_by_impl(Accessor f = Accessor{}) : _f(std::move(f)) {}

    template <typename T, typename U>
    bool operator()(T const& a, U const& b) const {
        return _f(a) < _f(b);
    }
  private:
    Accessor _f;
};

template <typename Accessor, typename F = typename boost::remove_reference<Accessor>::type >
compare_by_impl<F> comparer_by(Accessor&& f) {
    return compare_by_impl<F>(std::forward<Accessor>(f));
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

void Function()
{
    struct accessX_c_str {
        const char* operator()(bar const& b) const {
            return b.X->c_str();
        }
    };

    std::sort(Bs.begin(), Bs.end(), comparer_by(accessX_c_str()));
    std::sort(Bs.begin(), Bs.end(), phx::bind(accessX_c_str(), arg1) < phx::bind(accessX_c_str(), arg2));

    auto phxAccessor = phx::bind(&foo::c_str, phx::lambda [ phx::bind(&bar::X, arg1) ](arg1) );
    std::sort(Bs.begin(), Bs.end(), comparer_by(phxAccessor)); // this is where deduction is _very_ handy
    
    std::sort(Bs.begin(), Bs.end(), 
            phx::bind(&foo::c_str, phx::lambda [ phx::bind(&bar::X, arg1) ](arg1)) 
          < phx::bind(&foo::c_str, phx::lambda [ phx::bind(&bar::X, arg1) ](arg2))
        );
}

int main()
{
    Function();
}
