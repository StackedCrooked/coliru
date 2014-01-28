#include <iostream>

template < unsigned int i, char ... RHS > 
struct t { 
    constexpr static char const* s() { return t<i-1, ' ', char(i+'0'), RHS...>::s(); };
}; 

template <char ... RHS > 
struct t<0, RHS...> { 
    constexpr static char arr[]  = {'0', RHS..., '\0'};
    constexpr static char const* s() { return arr; }
};

template <char ... RHS > 
constexpr char t<0, RHS...>::arr[];

int main() {
    std::cout << t<5>::s(); // {'0',' ','1',' ','2',' ','3',' ','4',' ','5','\0'}
}