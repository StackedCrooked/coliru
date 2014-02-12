#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/phoenix.hpp>

namespace {
    template <typename T>
    struct make_shared_f
    {
        template <typename... A> struct result 
            { typedef boost::shared_ptr<T> type; };

        template <typename... A>
        typename result<A...>::type operator()(A&&... a) const {
            return boost::make_shared<T>(std::forward<A>(a)...);
        }
    };

    template <typename T>
    using make_shared_ = boost::phoenix::function<make_shared_f<T> >;
}

////////////////////////////////
// now we can have a ball!
using namespace boost::phoenix::arg_names;
#include <vector>
#include <iostream>

int main()
{
    typedef std::vector<int> IntVec;
    auto LazyInts = make_shared_<IntVec>()(arg1, arg2);

    // create a shared vector of 7 ints '42'
    auto ints = LazyInts(7, 42);
    for (auto i : *ints) std::cout << i << " ";
}
