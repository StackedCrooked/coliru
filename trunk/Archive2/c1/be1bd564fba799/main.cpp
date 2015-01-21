#include <iostream>
#include <cmath>
#include <iterator>
#include <algorithm>

int main() {
    auto isPerfect = [](int64_t maybeSquare) {
        int64_t r = sqrt(maybeSquare);
        return (r * r == maybeSquare);
    };

    int discard;
    if (std::cin>>discard) {
        std::transform(
                std::istream_iterator<int64_t>    (std::cin), {},
                std::ostream_iterator<const char*>(std::cout, "\n"),
                [isPerfect](int64_t value) { 
                    auto sqr = 5 * pow(value, 2);
                    return (isPerfect(sqr + 4) || isPerfect(sqr - 4))? "IsFibo" : "IsNotFibo";
                }
            );
    }
}
