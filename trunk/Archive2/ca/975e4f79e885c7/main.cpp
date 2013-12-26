#include <iostream>
#include <string>
#include <vector>

void purr ( char a ) {
    std::cout << "char" << std::endl;
    std::cout << a << std::endl;
}

void purr ( const char* a ) {
    std::cout << "const char*" << std::endl;
    std::cout << a << std::endl;
}

struct implicit {
    
    operator const char* () {
        return "meow";
    }
  
    template <typename T = int, typename X = typename std::enable_if<std::is_same<T, int>::value>::type>
    operator int () {
        return 42;
    } 
};

int main() {
    const char* meow = "meow";
    purr(meow);
    purr( implicit() );
    int convert = implicit{};
}
