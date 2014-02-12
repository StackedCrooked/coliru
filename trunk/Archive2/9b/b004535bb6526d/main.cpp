#include <fstream>
#include <type_traits> 

struct A {
    
};

int main() {
    A a(std::fstream(argv[1]));    
    static_assert(std::is_same<decltype(a), A(std::fstream[1])>::value, "");
}
