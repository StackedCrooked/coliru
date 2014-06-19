#include <iostream>

template<char... Cs>
struct String {};

template<typename T, char C>
struct PushBack_ {};

template<char... Cs, char C>
struct PushBack_<String<Cs...>, C> {
    using type = String<Cs..., C>;  
};

template<typename T, char C>
using PushBack = typename PushBack_<T, C>::type;

template<char... Cs>
void print(String<Cs...>) {
    char temp[] = {Cs..., '\0'};
    std::cout << temp;
}

int main() {
    using str = String<'a', 'b', 'c'>;
    using newStr = PushBack<str, 'f'>;
    
    print(newStr{});
}