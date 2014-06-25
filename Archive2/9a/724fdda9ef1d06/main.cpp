// test from Adrien Hamelin
// adrien.hamelin@irit.fr

#include <iostream>
#include <numeric>
#include <vector>

//*
template <typename Iter>
inline auto func(Iter iter, size_t i) -> decltype(iter += i) {

    return iter += i;

}
/*/
template <typename Iter>
inline Iter func(Iter const & iter, size_t i) {

    auto result(iter);
    return result += i;

}
//*/

int main()
{
    auto const size = 100u;
    std::vector<unsigned int> indices(size);
    auto const begin = std::begin(indices);

    std::iota(begin, func(begin, size), 0u);

    for (auto i = 0u; i < size; ++i) {
        if (indices[i] != i) {
            std::cout << "not working, indices[" << i << "] = " << indices[i] << std::endl;
            return 0;
        }
    }
    std::cout << "working" << std::endl;
    return 0;
}

