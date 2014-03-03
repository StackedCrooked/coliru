#include <iostream>
#include <type_traits>

class string {
public:
        template<typename T, typename = typename std::enable_if<std::is_same<T, const char*>::value>::type>
        string(const T) { std::cout << "p\n"; }

        template<size_t N>
        string(const char (&) [N]) { std::cout << "arr\n"; }
};


int main() {
        const char* c_str = "foo";
        string foo(c_str);
        string bar("bar");
}
