#include <iostream>
#include <utility>

#include <boost/coroutine/all.hpp>
#include <boost/variant/recursive_variant.hpp>

namespace boost {
namespace coroutines {

template<typename Sig>
auto begin(coroutine<Sig>& c)
-> decltype(boost::begin(c))
{ return boost::begin(c); }

template<typename Sig>
auto end(coroutine<Sig>& c)
-> decltype(boost::end(c))
{ return boost::end(c); }

} // coroutines
} // boost

template<typename T, typename U, typename V>
using tuple = std::pair<T, std::pair<U, V>>;
using tree = boost::make_recursive_variant<int, tuple<int, boost::recursive_variant_, boost::recursive_variant_>>::type;
using coro = boost::coroutines::coroutine<int()>;

struct node_visitor: boost::static_visitor<> {
    coro::caller_type* yield;

    explicit node_visitor(coro::caller_type& yield): yield(&yield) {}

    void operator()(int i) const
    {
        (*yield)(i);
    }

    void operator()(tuple<int, tree, tree> t) const
    {
        (*yield)(t.first);
        boost::apply_visitor(*this, t.second.first);
        boost::apply_visitor(*this, t.second.second);
    }
};

coro nodes(tree& t)
{
    return coro { [&t](coro::caller_type& yield) { node_visitor visitor { yield }; boost::apply_visitor(visitor, t); } };
}

int main()
{
    tree t { tuple<int, tree, tree> { 3, { tree { 42 }, tree { 121 } }  } };
    for(auto&& n: nodes(t)) std::cout << n << '\t';
    std::cout << '\n';
}