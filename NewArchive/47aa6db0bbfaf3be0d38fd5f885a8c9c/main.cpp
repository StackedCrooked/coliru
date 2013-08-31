#include <array>

template<class T, std::size_t size, std::size_t... Sizes>
class tensor {
public:
    
private:
    std::array<tensor<T, Sizes...>, size> elements;
};
template<class T, std::size_t size>
class tensor<T, size> {
public:
    
private:
    std::array<T, size> elements;
};

int main() {
    tensor<int, 3, 4, 5> arr;
}