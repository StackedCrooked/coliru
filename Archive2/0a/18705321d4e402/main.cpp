#include <iterator>
#include <cassert>

//A generic iterator class that repeats the sequence of the underlying iterators
//given a pair of iterators (first,last], dereferencing this iterator will result in that same sequence being repeated indefinitely
template<class it>
struct repeat_iterator {
    typedef typename std::iterator_traits<it>::value_type value_type;
    typedef typename std::iterator_traits<it>::reference reference;
    typedef typename std::iterator_traits<it>::pointer pointer;
    typedef typename std::iterator_traits<it>::difference_type difference_type;
    typedef std::input_iterator_tag iterator_category;
    
    //constructed from an index, and a pair of underlying iterators
    //the "first" repeat_iterator should have a repeat_count of zero
    //the "last" releat_iterator should have a repeat_count of however many iterations you want
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
//a helper function to make it easier to create repeat_iterators
template<class it>
repeat_iterator<it> make_repeat_iterator(int repeat_count, it first, it last) {return repeat_iterator<it>(repeat_count, first, last);}


#include <algorithm>
#include <iostream>

int main(void)
{
    //destination buffer
    unsigned char cbuffer[60] = {};
    //pattern of 6 bytes to fill with, with bytes 0x123456789ABC
    unsigned char fill[7] = "\x12\x34\x56\x78\x9A\xBC";
    
    //the source of the copy is two repeat iterators, 10 iterations apart, and give them pointers to the beginning and the end of the pattern buffer
    //the destination of the copy is a pointer to the cbuffer
    std::copy(make_repeat_iterator(0,fill+0,fill+6), make_repeat_iterator(10,fill+0,fill+6), cbuffer+0);
    
    //render all output in hexidecimal
    std::cout << std::hex;
    //now read out the bytes we copied into cbuffer
    for(unsigned char c : cbuffer)
        std::cout << +c;
    return 0;
}