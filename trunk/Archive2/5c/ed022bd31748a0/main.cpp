#include <iostream>
#include <limits>

template<typename A, typename B>
bool lt(A a, B b) {
    if (a < 0 && b >= 0)
        return true;
    if (a >= 0 && b < 0)
        return false;
    using TYPE = decltype(a + b);
    return static_cast<TYPE>(a) < static_cast<TYPE>(b);
}

template<typename X,typename Y,typename Z >
void checkParameter( X val, Y lower, Z upper) {
    if (lt(upper, val))
        std::cout << val << " > " << upper << std::endl;
    if (lt(val, lower))
        std::cout << val << " < " << lower << std::endl;
}


int main() {
    checkParameter(std::numeric_limits<int>::min(), 0u, std::numeric_limits<unsigned int>::max());
    checkParameter(std::numeric_limits<long long>::min(), 0u, std::numeric_limits<unsigned long long>::max());
    checkParameter(20u, 10.1, 30.5f);
}