#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>


#define TRACE //std::cout << __LINE__ << ":" << __PRETTY_FUNCTION__ << std::endl;


template<typename It>
struct IteratorRange
{
    auto begin() const { return b; }
    auto end() const { return e; }
    
    
    friend auto begin(const IteratorRange<It>& range) { return range.begin(); }
    friend auto end(const IteratorRange<It>& range) { return range.end(); }
    
    struct reverse_iterator
    {
        reverse_iterator(It b, It e) : b(e - 1), e(b - 1) { }
        
        // end iterator
        reverse_iterator(It b, It, int) : b(b - 1), e(b)
        {
            TRACE
        }
        
        reverse_iterator operator++()
        {
            TRACE
            --b;
            return *this;
        }
        
        auto operator*() const -> decltype(*std::declval<It>())
        {
            TRACE
            return *b;
        }
        
        friend bool operator!=(reverse_iterator lhs, reverse_iterator rhs)
        {
            TRACE
            return lhs.b != rhs.b;
        }
        
        It b, e;
        
    };
    
    auto rbegin() const { return reverse_iterator(b, e); }
    auto rend() const { return reverse_iterator(b, e, 0); }
        
    friend auto rbegin(const IteratorRange& range) { return range.rbegin(); }
    friend auto rend(const IteratorRange& range) { return range.rend(); }
    
    It b, e;
};


template<typename It>
auto make_range(It b, It e)
{
    TRACE
    return IteratorRange<It>{ b, e};
}


struct reversed_t { } reversed;


// requires range.rbegin() and range.rend()
template<typename Range>
auto operator|(Range&& range, reversed_t)
{
    TRACE
    return make_range(range.rbegin(), range.rend());
}


// accepts and array
// constructs IteratorRange<T> and then calls above overload
template<typename T, int N>
auto operator|(T (&array)[N], reversed_t)
{
    TRACE
    using namespace std;
    return make_range(begin(array), end(array)) | reversed;
}


int main()
{   
    // test with string
    for (auto i : std::string("123") | reversed) std::cout << i;    
    std::cout << std::endl;
    
    // test with array
    for (auto i : "123" | reversed) std::cout << i;
}


