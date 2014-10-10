#include <iostream>

#define AUTO_RETURN(...) -> decltype(__VA_ARGS__) {return (__VA_ARGS__);}

std::string GetDebugString(char ch) {return {ch};}
std::string GetDebugString(char const* str) {return str;}
std::string GetDebugString(std::string const& str) {return str;}

template <typename T>
auto GetDebugString( T t ) AUTO_RETURN(std::to_string(t))

// No AUTO_RETURN here because of GCC
template <typename T>
auto GetDebugString( T ptr ) -> decltype(GetDebugString(*ptr))
{
    return "Pointer to " + GetDebugString(*ptr);
}

template <typename T>
auto GetDebugString( T&& t ) AUTO_RETURN(std::forward<T>(t).DebugString())

template <typename Range>
auto GetDebugString( Range&& c ) -> decltype(std::begin(c), std::end(c), std::string())
{
    // Size obtainment can be optimized for containers with size member-functions
    std::string str = "Range with " + std::to_string(std::distance(std::begin(c), std::end(c))) + " elements: \n\t";
    for (auto const& elem : c)
        str += GetDebugString(elem) + ", ";
    return str;
}

int main()
{
    int i = 23;
    auto ptr = &i;
    char const str[] = "Hallo!";
    auto list = {4, 5, 5, 6, 8};

    std::cout << GetDebugString(i) << '\n';
    std::cout << GetDebugString(ptr) << '\n';
    std::cout << GetDebugString(str) << '\n';
    std::cout << GetDebugString(list) << '\n';
}