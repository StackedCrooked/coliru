#include <string>
#include <iostream>
#include <algorithm>

template<class Container>
Container combinations(Container last) {
    return last;
}

template<class Container, class... Containers>
Container combinations(Container curr, Containers... rest) {
    auto ret = Container();
    if (!curr.empty())
        for (auto i : curr)
            for (auto j : combinations(rest...))
                ret.push_back(i + j);
    else
        for (auto j : combinations(rest...))
                ret.push_back(j);
    return ret;
}

template<class Container>
void print_vec(Container vec) {
    for (auto x : vec)
        std::cout << x << '\n';
}

int main() {
    using strvec = std::vector<std::string>;
    
    auto ls = strvec{"a", "b", "c"};
    auto us = strvec{};
    auto ns = strvec{"-", "!", "?", "+"};
    
    int n = 3;
    switch (n) {
        case 2: print_vec(combinations(us, ls)); break;
        case 3: print_vec(combinations(ls, us, ns)); break;
        default: print_vec(combinations(ls));
    }
}