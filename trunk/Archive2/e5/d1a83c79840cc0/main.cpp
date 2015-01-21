#include <iostream>
#include <cmath>
#include <iterator>
#include <algorithm>

void optimize_io();

int main() {
    optimize_io();

    auto isPerfect = [](int64_t maybeSquare) {
        int64_t root = sqrt(maybeSquare);
        return (root * root == maybeSquare);
    };

    int discard;
    if (std::cin>>discard) {
        std::transform(
                std::istream_iterator<int64_t>    (std::cin), {},
                std::ostream_iterator<const char*>(std::cout, "\n"),
                [&](int64_t value) { 
                    auto sqr = 5 * pow(value, 2);
                    return (isPerfect(sqr + 4) || isPerfect(sqr - 4))? "IsFibo" : "IsNotFibo";
                }
            );
    }
}

void optimize_io() {
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
}
