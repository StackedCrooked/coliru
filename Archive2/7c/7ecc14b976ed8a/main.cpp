#include <iostream>
#include <stdexcept>
#include <typeinfo>
    
    
template<class... E>
struct my_catch;

template<>
struct my_catch<>
{
    void operator()() {
        throw;            
    }
};

template<class E0, class... E>
struct my_catch<E0, E...>
{
    void operator()() {
        try {
            throw;
        } catch (E0 const& ex) {
            std::cerr << ex.what() << " (" << typeid(ex).name() << ")" << std::endl;
        } catch (...) {
            my_catch<E...>{}();
        }       
    }
};

int main() {
    try {
        throw std::runtime_error("Hello");
    } catch (...) {
        my_catch<std::runtime_error, std::logic_error>{}();
    }
    
    try {
        throw std::logic_error("World");
    } catch (...) {
        my_catch<std::runtime_error, std::logic_error>{}();
    }

    return 0;
}


    
