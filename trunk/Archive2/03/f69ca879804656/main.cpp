#include <iostream>
#include <memory>
#include <type_traits>

namespace std
{
    // rename to "make_unique" instead of "make_unique2"
    template<typename T, typename... Args>
    unique_ptr<T> make_unique2( Args&&... ) { std::cout << "First" << std::endl; return unique_ptr<T>( new T() ); }
}

namespace check_unique
{
    template<typename... Args>
    void make_unique( Args&&... );
    
    using namespace std;
    
    struct has_make_unique : integral_constant<bool, !is_same<decltype(make_unique<shared_ptr<int>>(declval<shared_ptr<int>>())),void>::value> {};
}

namespace std
{
    // add only if no std::make_unique is already defined
    template<typename T, typename... Args>
    typename enable_if<!check_unique::has_make_unique::value, unique_ptr<T>>::type make_unique( Args&&... ) { std::cout << "Second" << std::endl; return unique_ptr<T>( new T() ); }
}

int main()
{
    std::make_unique<int>( 1 );
}
