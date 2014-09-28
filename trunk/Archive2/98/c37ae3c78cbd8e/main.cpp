#include <type_traits>

template <typename T>
struct optional {
    
};

static_assert(std::is_default_constructible<optional<int&>>(), ""); 

int main () {
    
}