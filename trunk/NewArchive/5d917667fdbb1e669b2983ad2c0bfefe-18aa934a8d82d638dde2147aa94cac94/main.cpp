#include <type_traits>

template <class T> 
struct RVector3 {
    static const int x = 10;
    T data[3];
};

static_assert(std::is_pod<RVector3<float>>(), "Told you it's a POD");

int main() {}