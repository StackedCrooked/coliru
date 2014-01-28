#include <vector>
#include <iterator>
#include <cassert>
#include <algorithm>

/*
template<class iterator_type>
void collatz_aux(unsigned n, iterator_type dst) {
    if (n != 1) {
        *dst = n;
        if (n % 2 == 0) {
            collatz_aux(n/2, ++dst);
        } else {
            collatz_aux(3 * n + 1, ++dst);
        }
    }
}
*/
template<class iterator_type>
void collatz_aux(unsigned n, iterator_type dst) {
    if (n != 1) {
        *dst = n;
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        collatz_aux(n, ++dst);
    }
}

std::vector<unsigned> collatz_vec(unsigned n) {
    assert(n != 0);
    std::vector<unsigned> result;
    collatz_aux(n, std::back_inserter(result));
    return result;
}

#include <iostream>
int main() {
    std::vector<unsigned> v = collatz_vec(10);
    std::cout << v.size() << '\n';
    std::copy(v.cbegin(), v.cend(), std::ostream_iterator<unsigned>(std::cout, ", "));
}