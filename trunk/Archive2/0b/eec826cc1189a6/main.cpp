
#include <iterator>
#include <cassert>

template<class iter, class category>
struct join_iterator_impl;

template<class iter>
struct join_iterator_impl<iter, std::forward_iterator_tag>
{
    typedef typename std::iterator_traits<iter>::value_type value_type;
    typedef typename std::iterator_traits<iter>::pointer pointer;
    typedef typename std::iterator_traits<iter>::reference reference;
    typedef typename std::iterator_traits<iter>::difference_type difference_type;
    typedef typename std::iterator_traits<iter>::iterator_category iterator_category;
    
    join_iterator_impl() : cur(), from(), to() {}
    join_iterator_impl(iter cur, iter from, iter to) : cur(cur), from(from), to(to) {}
    
    join_iterator_impl& operator++() {if (++cur==from) cur=to; return *this;}    
    join_iterator_impl operator++(int) {join_iterator_impl t(*this); operator++(); return t;}
    
    reference operator*() {return *cur;}
    iter operator->() {return cur;}
    
    friend bool operator==(const join_iterator_impl& lhs, const join_iterator_impl& rhs)
    {
        assert(lhs.from==rhs.from && lhs.to==rhs.to);
        return lhs.cur==rhs.cur;
    }
    friend bool operator!=(const join_iterator_impl& lhs, const join_iterator_impl& rhs)
    {return !(lhs==rhs);}
    
    friend void swap(join_iterator_impl& lhs, join_iterator_impl& rhs)
    {
        using std::swap;
        swap(lhs.cur, rhs.cur);
        swap(lhs.from, rhs.from);
        swap(lhs.to, rhs.to);
    }
protected:
    iter cur, from, to;
};

template<class iter>
struct join_iterator_impl<iter, std::bidirectional_iterator_tag>
: public join_iterator_impl<iter, std::forward_iterator_tag>
{
    join_iterator_impl() : join_iterator_impl<iter, std::forward_iterator_tag>() {}
    join_iterator_impl(iter cur, iter from, iter to)  : join_iterator_impl<iter, std::forward_iterator_tag>(cur, from, to) {}
    
    join_iterator_impl& operator--() {if (this->cur==this->to) this->cur=this->from; --this->cur; return *this;}    
    join_iterator_impl operator--(int) {join_iterator_impl t(*this); operator--(); return t;}
};

template<class iter>
struct join_iterator_impl<iter, std::random_access_iterator_tag>
: public join_iterator_impl<iter, std::bidirectional_iterator_tag>
{
    typedef typename std::iterator_traits<iter>::value_type value_type;
    typedef typename std::iterator_traits<iter>::pointer pointer;
    typedef typename std::iterator_traits<iter>::reference reference;
    typedef typename std::iterator_traits<iter>::difference_type difference_type;
    typedef typename std::iterator_traits<iter>::iterator_category iterator_category;
    
    join_iterator_impl() : join_iterator_impl<iter, std::bidirectional_iterator_tag>() {}
    join_iterator_impl(iter cur, iter from, iter to)  : join_iterator_impl<iter, std::bidirectional_iterator_tag>(cur, from, to) {}
    
    reference operator[](difference_type o) {return *(*this+o);}
    
    join_iterator_impl& operator+=(difference_type o) {difference_type safe=this->from-this->cur; if(safe<o) this->cur=this->to+o-safe; else this->cur+=o; return *this;}
    join_iterator_impl& operator-=(difference_type o) {difference_type safe=this->cur-this->to; if(safe<o) this->cur=this->from-o+safe; else this->cur-=o; return *this;}
    friend join_iterator_impl operator+(join_iterator_impl it, difference_type o) {return it+=o;}
    friend join_iterator_impl operator+(difference_type o, join_iterator_impl it) {return it+=o;}
    friend join_iterator_impl operator-(join_iterator_impl it, difference_type o) {return it-=o;}
    friend difference_type operator-(join_iterator_impl lhs, join_iterator_impl rhs) {
        assert(lhs.from==rhs.from && lhs.to==rhs.to);
        if (lhs.cur<lhs.from) 
        {
            if (rhs.cur<rhs.from)
                return lhs.cur-rhs.cur;
            else
                return (rhs.cur-rhs.to) + (lhs.from-lhs.cur);
        } 
        else 
        {
            if (rhs.cur<rhs.from)
                return (lhs.cur-lhs.to) + (rhs.from-rhs.cur);
            else
                return lhs.cur-rhs.cur;
        }
    }
    friend difference_type operator<(join_iterator_impl lhs, join_iterator_impl rhs) {
        assert(lhs.from==rhs.from && lhs.to==rhs.to);
        if (lhs.cur<lhs.from) 
        {
            if (rhs.cur<rhs.from)
                return lhs.cur<rhs.cur;
            else
                return true;
        } 
        else 
        {
            if (rhs.cur<rhs.from)
                return false;
            else
                return lhs.cur<rhs.cur;
        }
    }
    friend difference_type operator<=(join_iterator_impl lhs, join_iterator_impl rhs) {return lhs==rhs || lhs<rhs;}
    friend difference_type operator>=(join_iterator_impl lhs, join_iterator_impl rhs) {return !(lhs<rhs);}
    friend difference_type operator>(join_iterator_impl lhs, join_iterator_impl rhs) {return !operator<=(lhs,rhs);}
};

template<class iter>
struct join_iterator : public join_iterator_impl<iter, typename std::iterator_traits<iter>::iterator_category>
{
    join_iterator() : join_iterator_impl<iter, typename std::iterator_traits<iter>::iterator_category>() {}
    join_iterator(iter cur, iter from, iter to)  : join_iterator_impl<iter, typename std::iterator_traits<iter>::iterator_category>(cur, from, to) {}
};

template<class iter> join_iterator<iter> make_join_iter_first(iter first0, iter last0, iter first1, iter last1) {return join_iterator<iter>(first0, last0, first1);}
template<class iter> join_iterator<iter> make_join_iter_last(iter first0, iter last0, iter first1, iter last1) {return join_iterator<iter>(last1, last0, first1);}






#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ostream_iterator<int> out_it(std::cout);
    
    std::vector<int> container = {7, 3, 9, 4, 1, 0, 5, 3, 2, 8, 2, 0};
    auto wrap_it = container.begin() + 3;
    auto first = make_join_iter_first(wrap_it, container.end(), container.begin(), wrap_it);
    auto last = make_join_iter_last(wrap_it, container.end(), container.begin(), wrap_it);
    
    std::copy(first, last, out_it);
}