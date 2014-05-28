#ifndef HEADER_HPP
#define HEADER_HPP

# include <iterator>
# include <array>


/// Simple class to use a pair of iterators with foreach
template<class It>
class IteratorPair
{
    It _b, _e;
public:
    IteratorPair(It b, It e)
    : _b(b), _e(e)
    {}

    It begin() { return _b; }
    It end() { return _e; }
};

template<class T, bool(*filter)(T), class C>
class FilterIterator
{
    C *container;
    using InnerIterator = decltype(std::begin(*container));
    InnerIterator impl;
public:
    void post_adv()
    {
        while (impl != std::end(*container))
        {
            if (filter(*impl))
                break;
            ++impl;
        }
    }

    FilterIterator(C *c)
    : container(c), impl(std::begin(*c))
    {
        post_adv();
    }

    void operator ++()
    {
        ++impl;
        post_adv();
    }

    T operator *()
    {
        return *impl;
    }

    friend
    bool operator != (FilterIterator l, FilterIterator)
    {
        return l.impl != std::end(*l.container);
    }
};

template<class T>
bool is_truthy(T v)
{
    return v;
}

template<class T, bool(*filter)(T)=is_truthy, class C>
IteratorPair<FilterIterator<T, filter, C>> filter_iterator(C *c)
{
    return {FilterIterator<T, filter, C>(c), FilterIterator<T, filter, C>(c)};
}


void do_it();

class Session;

constexpr int MAX_MAP_SERVERS = 30;

auto iter_map_sessions() -> decltype(filter_iterator<Session *>(std::declval<std::array<Session *, MAX_MAP_SERVERS> *>()));

void frob(Session *);

#endif
