#include <iostream>
#include <vector>
#include <cmath>

std::vector<int64_t> readElements(int);
bool isPerfectSquare(int64_t sqrValue);

int main() {
    int input_count;
    if (!(std::cin >> input_count && (input_count > 0) && (input_count <= 100000))) {
        std::cout << "Total number of inputs out of range.\n";
        return 1;
    }

    auto const elements = readElements(input_count);

    /*iterate the elements from the list*/
    for (auto value : elements) {
        int64_t sqrValue = 5 * pow(value, 2);

        if (isPerfectSquare(sqrValue + 4) || isPerfectSquare(sqrValue - 4)) {
            std::cout << "IsFibo\n";
        } else {
            std::cout << "IsNotFibo\n";
        }
    }
}

#include <iterator>
#include <algorithm>

std::vector<int64_t> readElements(int input_count) {
    std::vector<int64_t> r;
    std::cin.exceptions(std::ios_base::eofbit);
    std::copy_n(std::istream_iterator<int64_t>(std::cin), input_count, back_inserter(r));
    return r;
}

bool isPerfectSquare(int64_t maybeSquare) {
    int64_t r = sqrt(maybeSquare);
    return (r * r == maybeSquare);
}
