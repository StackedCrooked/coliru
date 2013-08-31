#include <iterator>
#include <vector>
#include <iostream>

struct LezGo {
    
    template <typename TIterator, std::size_t value_size = sizeof( TIterator::value_type )>
    Meow ( TIterator arf, int c ) {
           std::cout << "Arf!\n"; 
    }
    
};

struct AllTheWay {
    
    template <typename TIterator>
    Meow<TIterator, 1> ( TIterator arf, int c ) {
        std::cout << "Woof!\n";
    }
    
};
    
int main () {
    
}