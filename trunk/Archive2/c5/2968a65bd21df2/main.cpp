
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <vector>

template <typename C>
    using Value_Type = typename std::remove_reference<decltype(*std::begin(std::declval<typename std::add_lvalue_reference<C>::type>()))>::type;

template<typename C, typename V>
std::vector<Value_Type<C>*> find_all(C& cont, V v)
{
    std::vector<Value_Type<C>*> res; 

    for (auto& x : cont) 
        if (x == v) 
            res.push_back(&x);

    return res;
}

int main()
{
    int array[] = {0, 1, 2, 3}; 
    for (const auto p: find_all(array, 2))
        std::cerr << *p; 
    std::cerr << "\n";
    std::string string = "Whatever you'll choose!";
    for (const auto p: find_all(string, 'e'))
    	std::cerr << *p; 
    std::cerr << "\n";
}