#include <string>
#include <iostream>

namespace dessert {
    template <typename Tag>
    struct not_quite_the_same_traits : std::char_traits<char> {};
    template <typename Tag>
    using strong_string_alias = std::basic_string<char, not_quite_the_same_traits<Tag>>;
    
    using vanilla_string = std::string;
    using strawberry_string = strong_string_alias<struct strawberry>;
    using caramel_string = strong_string_alias<struct caramel>;
    using chocolate_string = strong_string_alias<struct chocolate>;
    
    template <typename T>
    struct special;
    
    template <typename T>
    using special_string = strong_string_alias<special<T>>;
        
    template <typename CharT, typename CharTraits>
        std::basic_ostream<CharT, CharTraits>& operator<<(std::basic_ostream<CharT, CharTraits>& os, vanilla_string const& s) 
    {
        return os << "vanilla: " << s.data();
    }
    template <typename CharT, typename CharTraits>
        std::basic_ostream<CharT, CharTraits>& operator<<(std::basic_ostream<CharT, CharTraits>& os, strawberry_string const& s) 
    {
        return os << "strawberry: " << s.data();
    }
    template <typename CharT, typename CharTraits>
        std::basic_ostream<CharT, CharTraits>& operator<<(std::basic_ostream<CharT, CharTraits>& os, caramel_string const& s) 
    {
        return os << "caramel: " << s.data();
    }
    template <typename CharT, typename CharTraits>
        std::basic_ostream<CharT, CharTraits>& operator<<(std::basic_ostream<CharT, CharTraits>& os, chocolate_string const& s) 
    {
        return os << "chocolate: " << s.data();
    }
    
    template <typename CharT, typename CharTraits, typename T>
        std::basic_ostream<CharT, CharTraits>& operator<<(std::basic_ostream<CharT, CharTraits>& os, special_string<T> const& s) 
    {
        return os << "special: " << s.data();
    }
}

int main() {
    dessert::vanilla_string vanilla = "foo";
    dessert::strawberry_string strawberry = "foo";
    dessert::caramel_string caramel = "foo";
    dessert::chocolate_string chocolate = "foo";
    
    std::cout << vanilla << '\n';
    std::cout << strawberry << '\n';
    std::cout << caramel << '\n';
    std::cout << chocolate << '\n';
    
    dessert::special_string<struct nuts> nuts = "foo";
    std::cout << nuts << '\n';
}
