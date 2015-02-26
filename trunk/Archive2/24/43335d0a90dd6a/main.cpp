#include <iostream>
#include <vector>
#include <iterator>
#include <type_traits>

template<typename Iterator, typename T> 
bool contains (Iterator begin, Iterator end, const T& value) {
    
    static_assert(std::is_same<typename std::iterator_traits<Iterator>::value_type, T>::value, "Wrong Type");
    
     while(begin != end)
       if(*begin++ == value)
         return true;
     return false;
}

int main(){
    std::vector<int> v { 41, 42 };
    std::cout << contains(std::begin(v), std::end(v), 42);   // Good type
    std::cout << contains(std::begin(v), std::end(v), 43.0); // Wrong type
};