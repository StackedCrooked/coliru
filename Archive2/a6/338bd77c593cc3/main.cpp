#include<iostream>
#include <vector>

template<typename Iterator, typename T> 
bool contains (Iterator begin, Iterator end, T value) {
     while(begin != end)
       if(*begin++ == value)
         return true;
     return false;
}

int main(){
    std::vector<int> v { 41, 42 };
    std::cout << contains(std::begin(v), std::end(v), 42);
    std::cout << contains(std::begin(v), std::end(v), 43);
};
