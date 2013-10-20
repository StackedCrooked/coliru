#include <string>
#include <iostream>
#include <cctype>
 
struct ci_char_traits : public std::char_traits<char> {
    static bool eq(char c1, char c2) {
         return std::toupper(c1) == std::toupper(c2);
     }
    static bool ne(char c1, char c2) {
         return std::toupper(c1) != std::toupper(c2);
     }
    static bool lt(char c1, char c2) {
         return std::toupper(c1) <  std::toupper(c2);
    }
    static int compare(const char* s1, const char* s2, size_t n) {
        while ( n-- != 0 ) {
            if ( std::toupper(*s1) < std::toupper(*s2) ) return -1;
            if ( std::toupper(*s1) > std::toupper(*s2) ) return 1;
            ++s1; ++s2;
        }
        return 0;
    }
    static const char* find(const char* s, int n, char a) {
        while ( n-- > 0 && std::toupper(*s) != std::toupper(a) ) {
            ++s;
        }
        return s;
    }
};
 
typedef std::basic_string<char, ci_char_traits> ci_string;
 
std::ostream& operator<<(std::ostream& os, const ci_string& str) {
    return os.write(str.data(), str.size());
}

std::istream& operator>>(std::istream& in, ci_string& str)
{
    std::string tmp;
    in >> tmp;
    str = tmp.c_str(); 
    return in;
} 

int main()
{
    ci_string test_str; 
    std::cin >> test_str; 
    std::cout << test_str; 
    return 0; 
} 
