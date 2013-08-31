#include <cassert>

int main() {
    char const* a = "hello";
    char const b[] = "hello";
    
    assert(a != b);
}