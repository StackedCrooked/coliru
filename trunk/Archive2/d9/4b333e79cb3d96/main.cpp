#include <iostream>
#include <cstdlib>

template<typename T, std::size_t M, std::size_t N>
struct array2d_view
{
    array2d_view(T (&arr)[M][N]) : arr_(&arr[0][0]) {}
    T *arr_;
    T *begin() { return arr_; }
    T *end() { return arr_ + M*N; }
};

int main()
{
    int arr[4][10] = {};
    array2d_view<int, 4, 10> view(arr);
    
    for(auto&& i : view) {
        i = 42;
    }
    
    for(auto const& a : arr) {
        for(auto const& b : a) {
            std::cout << b << ' ';
        }
        std::cout << '\n';
    }
}
