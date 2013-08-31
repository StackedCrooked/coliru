#include <type_traits>

template<class T, int count>
struct array {
    array() : data() {}
    
    template<int N>
    T& operator[](std::integral_constant<int,N> index) {
        char index_is_too_large[(N<count)*2-1]={};
        index_is_too_large[0] = index_is_too_large[0];
                
        return data[N];
    }
private:
    T data[count];
};

#include <iostream>
int main() {
    array<float, 3> thingy;

    std::integral_constant<int, 2> index2;
    std::cout << thingy[index2] << '\n';

    std::integral_constant<int, 3> index3;
    std::cout << thingy[index3] << '\n';
}