#include <utility>
#include <thread>

void f(char const* const & c){}
template<size_t N> void f(char const(&a)[N]){}

int main() {

    f("hello"); // print ptr, ok because this is the fixed size array
    f(std::string("hello").c_str()); // print arr, ok because `c_str()` is a pointer
}