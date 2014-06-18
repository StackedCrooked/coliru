#include <functional>
#include <iostream>
#include <vector>

template <typename It, 
          typename Pred, 
          typename Comp = std::less<decltype(*std::declval<It>())>>
It minElementWhere(
    It begin,
    It end,
    Pred pred = Pred(),
    Comp comp = Comp()
) {
    It minElement = end;

    for (It it = begin; it != end; ++it) {
        if (!pred(*it)) {
            continue;
        }

        if (comp(*it, *minElement)) {
            minElement = it;
        }
    }

    return minElement;
}

int main() {
    std::vector<double> foo;
    foo.push_back(6);
    foo.push_back(10);
    foo.push_back(-3);
    foo.push_back(7);

    std::cout << *minElementWhere(
        foo.begin(),
        foo.end(),
        [](double val) {
            return val >= 0;
        }
    ) << std::endl;
}
