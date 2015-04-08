#include <string>
#include <iostream>
#include <cctype>
 
struct ci_char_traits : public std::char_traits<char> {
    static bool eq(char c1, char c2) {
         return std::toupper(c1) == std::toupper(c2);
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
        auto const ua (std::toupper(a));
        while ( n-- != 0 ) 
        {
            if (std::toupper(*s) == ua)
                return s;
            s++;
        }
        return nullptr;
    }
};
 
typedef std::basic_string<char, ci_char_traits> ci_string;
 
std::ostream& operator<<(std::ostream& os, const ci_string& str) {
    return os.write(str.data(), str.size());
}
 
int main()
{
    ci_string s1 = "Hello";
    ci_string s2 = "heLLo";
    if (s1 == s2)
        std::cout << s1 << " and " << s2 << " are equal\n";
}