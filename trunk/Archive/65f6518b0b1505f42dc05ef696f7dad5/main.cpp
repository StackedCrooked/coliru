#include <array>

template<class T, std::size_t size, std::size_t... Sizes>
struct tensor {
    typedef std::array<typename tensor<T, Sizes...>::type, size> type;    
};
template<class T, std::size_t size>
struct tensor<T, size> {
    typedef std::array<T, size> type;
};

int main() {
    tensor<int, 3, 4, 5>::type arr;
}