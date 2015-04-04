#include <iostream>
#include <iterator>
#include <vector>
#include <utility>

template<typename Range1, typename Range2, typename OutputIterator>
void cartesian_product(Range1 const &r1, Range2 const &r2, OutputIterator out) {
    using std::begin; using std::end;
    
    for (auto i = begin(r1);i != end(r1); ++i) {
        for (auto j = begin(r2); j != end(r2); ++j) {
            *out++ = std::make_tuple(*i, *j);
        }
    }
}

template<typename T, int N> constexpr int size(T (&)[N]) { return N; }

int main() {
    int M[2]= {1,2};
    int J[3] = {0,1,2};

    std::tuple<int, int> product[size(M) * size(J)];

    cartesian_product(M, J, product);

    for (auto &&v : product) {
        std::cout << "(" << std::get<0>(v) << "," << std::get<1>(v) << ")";
    }
}