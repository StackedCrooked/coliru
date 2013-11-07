#include <iostream>


// helper for decltype-based sfinae
template<typename T, typename ...U>
T get_type(U&&...);


// print object by using .to_string() if it exists
template<typename T>
auto print_impl(std::ostream& os, T&& t, int) //-> decltype(get_type<void>(t.to_string())) // detect to_string
                                              -> decltype(t.to_string(), void())
{
    os << t.to_string();
}


// print object using stream operator
template<typename T>
void print_impl(std::ostream& os, T&& t, long)
{
    os << t;
}


template<typename T>
void print(std::ostream& os, T&& t)
{
    print_impl(os, t, int{});
}



int main()
{
    print(std::cout, 1);
    
    struct Item
    {
        const char* to_string() const { return "Item"; }
    };    
    
    print(std::cout, Item());
}