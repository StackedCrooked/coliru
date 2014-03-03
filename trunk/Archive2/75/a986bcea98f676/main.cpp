#include <cstddef>
#include <iostream>
#include <type_traits> 

class string {
public:
    template<typename T, typename = typename std::enable_if<std::is_same<T, const char *>::value>::type>
    string(const T &) {std::cout << "const char *\n";}
    
    template<typename T, std::size_t N, typename = typename std::enable_if<std::is_same<T, char>::value>::type>
    string(const T(&)[N]) {std::cout << "const char(&)[" << N << "]\n";}
};

int main() {
    const char* c_str = "foo";
    string s("foo");
    string s2(c_str);
}