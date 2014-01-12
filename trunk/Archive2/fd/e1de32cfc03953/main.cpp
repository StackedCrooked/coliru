// Refer http://ericniebler.com/2013/11/07/input-iterators-vs-input-ranges/ ,
//       http://boost.2283326.n4.nabble.com/range-fat-iterators-td4654575.html

#include <boost/iterator/iterator_facade.hpp>
#include <type_traits>
#include <iterator>
#include <iostream>
#include <cassert>

using namespace boost;
using namespace std;

template<typename TrivialInputIterator>
class InputRangeAdaptor
{
    mutable TrivialInputIterator it;
    // Cache during increment?
    // Or maybe underlying iterator/range should do it by himself.

    // iterator_traits?
    using reference = decltype(*it);
    using value_type = typename std::remove_reference<reference>::type;
public:
    class iterator: public iterator_facade
                    <
                        iterator, value_type, input_iterator_tag, reference
                    >
    {
        const InputRangeAdaptor *range = nullptr;
    public:
        iterator() = default;
        explicit iterator(const InputRangeAdaptor &range)
            : range{empty(range.it) ? nullptr : &range}
        {}
    private:
        friend class boost::iterator_core_access;
        void increment()
        {
            ++range->it;
            if(empty(range->it))
                range = nullptr;
        }
        bool equal(iterator x) const
        {
            return range == x.range;
            // Another option: move checks for emptiness here from increment.
            // That would be faster for cases when we do not check for equality,
            //   i.e. std::copy_n.
            // But such equality check will be more complicated and slower
        }
        reference dereference() const
        {
            return *range->it;
        }
    };

    explicit InputRangeAdaptor(TrivialInputIterator it)
        : it(it)
    {}
    
    iterator begin() const
    {
        return iterator{*this};
    }
    iterator end() const
    {
        return iterator{};
    }
};

template<typename TrivialInputIterator>
InputRangeAdaptor<TrivialInputIterator> make_range(TrivialInputIterator x)
{
    return InputRangeAdaptor<TrivialInputIterator>{x};
}

/*****************************************************************************/

class NullTerminated  // Models TrivialInputIterator
{
    const char *position;
public:
    explicit NullTerminated(const char *position)
        : position{position}
    {}
    NullTerminated &operator++()
    {
        ++position;
        return *this;
    }
    const char &operator*() const
    {
        return *position;
    }
    friend bool empty(const NullTerminated &x)
    {
        return *x == 0;
    }
};

/*****************************************************************************/

#include <initializer_list>
#include <iterator>
#include <cassert>
#include <vector>

// NOT TESTED!
template<typename Outer>
class JaggedIterator // Models TrivialInputIterator
{
    Outer first, last;
    using Inner = decltype(begin(*first)); // TODO: use iterator_traits
    Inner inner_first;
    using value_type = decltype(*inner_first);
    
    void skip_empty()
    {
        assert(first != last);
        while(inner_first == end(*first))
        {
            ++first;
            if(first == last) break;
            inner_first = begin(*first);
        }
    }
    void inner_to_begin()
    {
        if(first != last)
        {
            inner_first = begin(*first);
            skip_empty();
        }
    }
public:
    JaggedIterator(Outer first, Outer last)
        : first(first), last(last)
    {
        inner_to_begin();
    }
    JaggedIterator &operator++()
    {
        if(inner_first != end(*first))
            ++inner_first;
        if(first != last)
            skip_empty();

        return *this;
    }
    const int &operator*() const
    {
        return *inner_first;
    }
    friend bool empty(const JaggedIterator &x)
    {
        return x.first == x.last;
    }
};

template<typename Outer>
auto make_jagged(Outer first, Outer last)
{
    return JaggedIterator<Outer>{first, last};
}

int main()
{
    using namespace std;
    vector<vector<int>> x = {{}, {}, {1,2,3}, {}, {4, 5, 6}, {7,8}, {9}};

    for(auto x : make_range(make_jagged(begin(x), end(x))))
        cout << x << " ";
    cout << endl;
}
