#include <cassert>
#include <vector>

struct foo {
    std::vector<std::vector<int>> vec;
    foo (std::size_t rows, std::size_t cols) : vec(rows, std::vector<int>(cols, 5)) {}
    void invert() {
        assert(vec.size() == vec.front().size());
        for (std::size_t i = 0; i < vec.size(); ++i) {
            for (std::size_t j = 0; j < vec.size(); ++j) {
                std::swap(vec[i][j], vec[j][i]);
            }
        }
    }
    auto begin() const {
        return std::begin(vec);
    }
    auto end() const {
        return std::end(vec);
    }
};

#include <iostream>

std::ostream & operator<<(std::ostream & out, const foo & f) {
    out << '{';
    for (const auto & row : f) {
        for (const auto & elem : row) {
            out << elem << ", ";
        }
        out << ';';
    }
    out << '}';
    return out << ';';
}

int main() {
    foo f(3, 4);
    std::cout << f;
}
