#include <cstddef>
#include <iostream>
#include <type_traits> 

class string {
public:
    template<typename T, typename = typename std::enable_if<std::is_same<T, char>::value>::type>
    string(const T * const &) {std::cout << "const char *\n";}
    
    template<std::size_t N>
    string(const char(&)[N]) {std::cout << "const char(&)[" << N << "]\n";}
};

int main() {
    const char* c_str = "foo";
    string s("foo");
    string s2(c_str);
}