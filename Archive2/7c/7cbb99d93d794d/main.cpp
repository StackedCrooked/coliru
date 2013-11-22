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

class DigitsIterator
{
    int current = 0;
public:
    DigitsIterator &operator++()
    {
        ++current;
        return *this;
    }
    const int &operator*() const
    {
        return current;
    }
    friend bool empty(DigitsIterator x)
    {
        return x.current == 10;
    }
};

class NullTerminated
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

int main()
{
    for(auto x : make_range(DigitsIterator{}))
        cout << x << " ";
    cout << endl;

    for(auto x : make_range(NullTerminated{"Sentinel iteration"}))
        cout << x;
    cout << "!" << endl;
}
