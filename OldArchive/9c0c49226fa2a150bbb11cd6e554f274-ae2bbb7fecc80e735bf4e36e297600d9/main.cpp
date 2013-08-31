#include <iostream>
#include <string>

template<typename M, typename... Args>
M make(Args... args) {
    M my_m = { args... };
    return my_m;
}

struct abc {
    int x;
    std::string y;
    float p;
};

struct snag {
    int a, b, c, d, e, f;
};

int main()
{
    auto oh = make<snag>(5, 6, 9, 7, 2, 3);
    auto my = make<abc>(12, "hello", 1.2f);
    std::cout << oh.f << " " << my.y << std::endl;
}
