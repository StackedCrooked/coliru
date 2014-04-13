#include <iterator>
#include <cassert>

template<class iter, class category>
struct only_N_iterator_impl;

template<class iter>
struct only_N_iterator_impl<iter, std::forward_iterator_tag>
{
    typedef typename std::iterator_traits<iter>::value_type value_type;
    typedef typename std::iterator_traits<iter>::pointer pointer;
    typedef typename std::iterator_traits<iter>::reference reference;
    typedef typename std::iterator_traits<iter>::difference_type difference_type;
    typedef typename std::iterator_traits<iter>::iterator_category iterator_category;
    
    only_N_iterator_impl() : base(), count(0), max(0) {}
    only_N_iterator_impl(iter base, int index, int max) : base(base), count(index), max(max) {}
    
    only_N_iterator_impl& operator++() {++count; ++base; return *this;}    
    only_N_iterator_impl operator++(int) {only_N_iterator_impl t(*this); operator++(); return t;}
    
    reference operator*() {return *base;}
    iter operator->() {return base;}
    
    friend bool operator==(const only_N_iterator_impl& lhs, const only_N_iterator_impl& rhs)
    {
        assert(lhs.max==rhs.max);
        return lhs.base==rhs.base || lhs.count==lhs.max;
    }
    friend bool operator!=(const only_N_iterator_impl& lhs, const only_N_iterator_impl& rhs)
    {return !(lhs==rhs);}
    
    friend void swap(only_N_iterator_impl& lhs, only_N_iterator_impl& rhs)
    {
        using std::swap;
        swap(lhs.base, rhs.base);
        swap(lhs.count, rhs.count);
        swap(lhs.max, rhs.max);
    }
protected:
    iter base;
    int count;
    int max;
};

template<class iter>
struct only_N_iterator_impl<iter, std::bidirectional_iterator_tag>
: public only_N_iterator_impl<iter, std::forward_iterator_tag>
{
    only_N_iterator_impl() : only_N_iterator_impl<iter, std::forward_iterator_tag>() {}
    only_N_iterator_impl(iter base, int index, int max)  : only_N_iterator_impl<iter, std::forward_iterator_tag>(base, index, max) {}
    
    only_N_iterator_impl& operator--() {--this->count; --this->base; return *this;}    
    only_N_iterator_impl operator--(int) {only_N_iterator_impl t(*this); operator--(); return t;}
};

template<class iter>
struct only_N_iterator_impl<iter, std::random_access_iterator_tag>
: public only_N_iterator_impl<iter, std::bidirectional_iterator_tag>
{
    typedef typename std::iterator_traits<iter>::value_type value_type;
    typedef typename std::iterator_traits<iter>::pointer pointer;
    typedef typename std::iterator_traits<iter>::reference reference;
    typedef typename std::iterator_traits<iter>::difference_type difference_type;
    typedef typename std::iterator_traits<iter>::iterator_category iterator_category;
    
    only_N_iterator_impl() : only_N_iterator_impl<iter, std::bidirectional_iterator_tag>() {}
    only_N_iterator_impl(iter base, int index, int max)  : only_N_iterator_impl<iter, std::bidirectional_iterator_tag>(base, index, max) {}
    
    reference operator[](difference_type o) {return *(*this+o);}
    
    only_N_iterator_impl& operator+=(difference_type o) {assert(this->max-this->count>=o); this->count+=o; this->base+=o; return *this;}
    only_N_iterator_impl& operator-=(difference_type o) {assert(o<=this->count); this->count-=o; this->base-=o; return *this;}
    friend only_N_iterator_impl operator+(only_N_iterator_impl it, difference_type o) {return it+=o;}
    friend only_N_iterator_impl operator+(difference_type o, only_N_iterator_impl it) {return it+=o;}
    friend only_N_iterator_impl operator-(only_N_iterator_impl it, difference_type o) {return it-=o;}
    friend difference_type operator-(only_N_iterator_impl lhs, only_N_iterator_impl rhs) {return lhs.count-rhs.count;}
};

template<class iter>
struct N_iterator : public only_N_iterator_impl<iter, typename std::iterator_traits<iter>::iterator_category>
{
    N_iterator() : only_N_iterator_impl<iter, typename std::iterator_traits<iter>::iterator_category>() {}
    N_iterator(iter base, int index, int max)  : only_N_iterator_impl<iter, typename std::iterator_traits<iter>::iterator_category>(base, index, max) {}
};

template<class iter> N_iterator<iter> make_N_iter_first(iter base, int max) {return N_iterator<iter>(base, 0, max);}
template<class iter> N_iterator<iter> make_N_iter_last(iter base, int max) {return N_iterator<iter>(base, max, max);}






#include <algorithm>
#include <iostream>
#include <list>

int main() {
    std::list<int> container = {7, 3, 9, 4, 1, 0, 5, 3, 2, 8, 2, 0};
    std::ostream_iterator<int> out_it(std::cout);
    
    auto first = make_N_iter_first(container.begin(), 5);
    auto last = make_N_iter_last(container.end(), 5); //technically any iterator after the fifth will act MOSTLY identically, unless it's decremented :(
    
    std::copy(first, last, out_it);
}