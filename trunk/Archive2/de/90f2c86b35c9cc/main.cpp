#include <cstdlib>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <iostream>
#include <array>

namespace sort_selector{
    template<typename T>
    void _radix_sort(T begin, T end){
        // radix implementation
    }

    template<typename T>
    typename std::enable_if<std::is_same<typename std::iterator_traits<T>::value_type, int64_t>::value>::type
    sort(T begin, T end){
        std::cout << "Doing radix with int64_t" << std::endl;
        sort_selector::_radix_sort(begin, end);
    }

    template<typename T>
    typename std::enable_if<
                  std::is_same<typename std::iterator_traits<T>::value_type, int32_t>::value>::type
    sort(T begin, T end){
        std::cout << "Doing radix with int32_t" << std::endl;
        sort_selector::_radix_sort(begin, end);
    }

    template<typename T>
    typename std::enable_if<!std::is_integral<typename std::iterator_traits<T>::value_type>::value>::type
    sort(T begin, T end){
        std::cout << "Doing sort" << std::endl;
        std::sort(begin, end);
    }
}
int main() {
    std::vector<double> for_stdsort = {1, 4, 6, 2};
    std::vector<int32_t> for_radixsort = {1, 4, 6, 2};
    std::vector<int64_t> for_radixsort_64 = {1, 4, 6, 2};
    std::array<int32_t, 4> array_for_radixsort = {1, 4, 6, 2};

    sort_selector::sort(std::begin(for_stdsort), std::end(for_stdsort));
    sort_selector::sort(std::begin(for_radixsort), std::end(for_radixsort));
    sort_selector::sort(std::begin(for_radixsort_64), std::end(for_radixsort_64));
    sort_selector::sort(std::begin(array_for_radixsort), std::end(array_for_radixsort));

    return 0;
}