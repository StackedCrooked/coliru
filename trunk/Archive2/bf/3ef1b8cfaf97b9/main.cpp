#include <iostream>
#include <functional>

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/adaptor/strided.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/iterator_range_core.hpp>

namespace range = boost::range;
namespace R = boost::adaptors;

template<typename BidiRange>
auto diffs(BidiRange&& in)
{
    using std::next;
    using std::prev;
    using boost::begin;
    using boost::end;
    using boost::empty;
    using boost::get;
    assert( !empty(in) );
    auto offset = [](auto&& in) { return boost::make_iterator_range(std::next(begin(in)), end(in)); };
    auto shave = [](auto&& in) { return boost::make_iterator_range(begin(in), std::prev(end(in))); };
    return R::transform(range::combine(R::stride(shave(in), 2), R::stride(offset(in), 2))
                        , [](auto const& elems) { return get<0>(elems) < get<1>(elems); } );
}

int main()
{
    auto in = { 1, 2, 3, 4, 5, 6 };
    auto d = diffs(in);
    using boost::get;
    for(auto const& item: d)
        std::cout << std::boolalpha << item << '\n';
}