#include <array>

// helper for calculating products at compile-time
template<std::size_t... Ns>
struct product;

template<std::size_t N>
struct product<N>
{
    static constexpr std::size_t value = N;
};

template<std::size_t N, std::size_t... Ns>
struct product<N, Ns...>
{
    static constexpr std::size_t value = N*product<Ns...>::value;
};

// Tensor_View is a tensor that doesn't own its array
template<typename T, std::size_t... Ds>
struct Tensor_View;

template<typename T, std::size_t N, std::size_t D>
struct Tensor_View<T, N, D>
{
    std::array<T, N>& a_;
    std::size_t start_;

    T& operator[](std::size_t i) {
        return a_[i + start_];
    }
};

template<typename T, std::size_t N, std::size_t D, std::size_t... Ds>
struct Tensor_View<T, N, D, Ds...>
{
    std::array<T, N>& a_;
    std::size_t start_;

    Tensor_View<T, N, Ds...> operator[](std::size_t i) {
        return {a_, start_ + i*product<Ds...>::value};
    }
};

// Tensor is a generic N-dimensional tensor
template<typename T, std::size_t... Ds>
struct Tensor;

// first order tensor
template<typename T, std::size_t D>
struct Tensor<T, D>
{
    std::array<T, D> a_ = {};

    T& operator[](std::size_t i) {
        return a_[i];
    }
};

// higher order tensor
template<typename T, std::size_t D, std::size_t... Ds>
struct Tensor<T, D, Ds...>
{
    static constexpr std::size_t N = product<D, Ds...>::value;
    std::array<T, N> a_ = {};

    Tensor_View<T, N, Ds...> operator[](std::size_t i) {
        return {a_, i*N/D};
    }
};


#include <iostream>
#include <iomanip>

// print out a 3D tensor
template<typename T, std::size_t N, std::size_t M, std::size_t O, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, Tensor<T, N, M, O> t) {
    for (auto i = 0; i < N; ++i) {
        os << std::endl;
        for (auto j = 0; j < M; ++j) {
            for (auto k = 0; k < O; ++k) {
                os << std::setw(4) << t[i][j][k] << ' ';
            }
            os << std::endl;
        }
        os << std::endl;
    }
    return os;
}

int main() {
    std::cout << "3D tensor:" << std::endl;
    
    Tensor<float, 2, 3, 4> t3;

    t3[0][0][0] = 1.1f;
    t3[0][2][1] = 2.2f;
    t3[1][2][1] = 3.3f;

    std::cout << t3;

    return 0;
}
