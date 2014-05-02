#include <cstdio>


// clang++ won't accept this, and it should...

template<typename T, T... t>
struct proxy {
    static constexpr T stuff[] = { (t+1)... };
};


int main() {
    proxy<int,1,1,1,1,1,1> x;
    printf("%d\n",x.stuff[3]);
    return {};
}