#include <iostream>
#include <numeric>

namespace std {

    template<class T, std::size_t N, std::size_t M>
    T* begin(T (&array)[N][M]) {
        return &array[0][0];
    }
    
    template<class T, std::size_t N, std::size_t M>
    T* end(T (&array)[N][M]) {
        return &array[0][0] + sizeof(array) / sizeof(array[0][0]);
    }

}

int main() {
    char a[2][2] = {{77, 3}, {8, 2}};
    int s = std::accumulate(std::begin(a), std::end(a), 0);
    std::cout << s;
}