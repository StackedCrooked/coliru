#include <iterator>
#include <cassert>

template<class it>
struct repeat_iterator {
    typedef typename std::iterator_traits<it>::value_type value_type;
    typedef typename std::iterator_traits<it>::reference reference;
    typedef typename std::iterator_traits<it>::pointer pointer;
    typedef typename std::iterator_traits<it>::difference_type difference_type;
    typedef std::input_iterator_tag iterator_category;
    
    repeat_iterator(int repeat_count, it first, it last) : cur(first), first(first), last(last), repeat_count(repeat_count) {}
    
    repeat_iterator& operator++() {if (++cur==last) {++repeat_count; cur=first; } return *this;}
    reference operator*() const {return *cur;}
    bool operator==(const repeat_iterator& rhs) const {assert(first==rhs.first&&last==rhs.last); return repeat_count==rhs.repeat_count;}
    bool operator!=(const repeat_iterator& rhs) const {assert(first==rhs.first&&last==rhs.last); return repeat_count!=rhs.repeat_count;}
    
    it cur;
    it first;
    it last;
    unsigned repeat_count;
};
template<class it>
repeat_iterator<it> make_repeat_iterator(int repeat_count, it first, it last) {return repeat_iterator<it>(repeat_count, first, last);}


#include <algorithm>
#include <iostream>

int main(void)
{
    unsigned char cbuffer[60] = {};
    unsigned char fill[7] = "\x12\x34\x56\x78\x9A\xBC";
    
    std::copy(make_repeat_iterator(0,fill+0,fill+6), make_repeat_iterator(10,fill+0,fill+6), cbuffer+0);
    
    std::cout << std::hex;
    for(unsigned char c : cbuffer)
        std::cout << +c;
    return 0;
}