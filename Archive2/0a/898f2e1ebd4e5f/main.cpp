#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <type_traits>
    

struct IteratorOutOfRange : std::out_of_range
{
    IteratorOutOfRange() : std::out_of_range("SafeIterator out of range.") {}
};


template<typename IteratorType>
struct SafeIterator
{
    using value_type = typename std::remove_const<typename std::remove_reference<decltype(*std::declval<IteratorType>())>::type>::type;
    
    SafeIterator(IteratorType b, IteratorType e) : b(b), e(e) {}
    
    value_type operator*()
    {
        check();
        return *b;
    }
    
    SafeIterator& operator++()
    {
        check();
        return ++b;
    }
    
    SafeIterator operator++(int)
    {
        check();
        return SafeIterator(b++, e);
    }
    
    bool is_valid() const
    {
        return b != e;
    }
    
    void check()
    {
        if (b == e) throw IteratorOutOfRange();
    }
    
    IteratorType b, e;
};


template<typename Container>
auto safe_begin(Container&& container) -> SafeIterator<typename std::remove_const<typename std::remove_reference<decltype(std::declval<Container>().begin())>::type>::type>
{
    return SafeIterator<typename std::remove_const<typename std::remove_reference<decltype(std::declval<Container>().begin())>::type>::type>(container.begin(), container.end());
}


int main()
{
    std::vector<int> vec = { 1, 2, 3 };
    
    auto it = safe_begin(vec);
    
    std::cout << *it++ << std::endl; // OK
    std::cout << *it++ << std::endl; // OK
    std::cout << *it++ << std::endl; // OK
    std::cout << *it++ << std::endl; // Throws exception!
}
