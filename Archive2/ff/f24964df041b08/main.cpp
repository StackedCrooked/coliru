#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <type_traits>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


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
    
    void check()
    {
        if (b == e) throw std::out_of_range("SafeIterator out of range.");
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
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    
    auto it = safe_begin(words);
    
    std::cout << *it++ << std::endl;
    std::cout << *it++ << std::endl;
    std::cout << *it++ << std::endl;
    std::cout << *it++ << std::endl;
    std::cout << *it++ << std::endl;
    std::cout << *it++ << std::endl;
    std::cout << *it++ << std::endl;
}
