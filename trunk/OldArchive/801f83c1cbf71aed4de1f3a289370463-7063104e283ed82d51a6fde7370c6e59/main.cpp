#include <iterator>
#include <vector>
#include <iostream>

struct LezGo {
    
    template <typename TIterator, std::size_t value_size = sizeof( TIterator )>
    void Meow ( TIterator arf, int c ) {
           std::cout << "Arf!\n"; 
    }
    
};

struct AllTheWay : public LezGo {
    using LezGo::Meow;
    
    template <typename TIterator>
    void Meow<TIterator, 1> ( TIterator arf, int c ) {
        std::cout << "Woof!\n";
    }
    
};
    
int main () {
    AllTheWay w;
    char onesized;
    int foursized;
    w.Meow( foursized, 20 );
    w.Meow( onesized, 20 );
}