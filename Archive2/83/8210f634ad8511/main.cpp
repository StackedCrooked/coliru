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

// 0-dim tensor is a scalar
template<typename T>
struct Tensor<T>
{
    T val_;
    
    Tensor<T>& operator=(T const& val) {
        val_ = val;
        return *this;
    }

    operator T&() {
        return val_;
    }
};

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

template<typename CharT, typename Traits, typename T, std::size_t P, std::size_t... Ns>
struct Tensor_View_Printer;

template<typename CharT, typename Traits, typename T, std::size_t P, std::size_t N>
struct Tensor_View_Printer<CharT, Traits, T, P, N>
{
    static void print(std::basic_ostream<CharT, Traits>& os, Tensor_View<T, P, N> t) {
        for (auto i = 0; i < N; ++i) {
            os << std::setw(4) << t[i] << ' ';
        }
        os << std::endl;
    };
};

template<typename CharT, typename Traits, typename T, std::size_t P, std::size_t N, std::size_t... Ns>
struct Tensor_View_Printer<CharT, Traits, T, P, N, Ns...>
{
    static void print(std::basic_ostream<CharT, Traits>& os, Tensor_View<T, P, N, Ns...> t) {
        for (auto i = 0; i < N; ++i) {
            Tensor_View_Printer<CharT, Traits, T, P, Ns...>::print(os, t[i]);
        }
        os << "---------" << std::endl;
    };
};

template<typename CharT, typename Traits, typename T, std::size_t... Ns>
struct Tensor_Printer;

template<typename CharT, typename Traits, typename T, std::size_t N>
struct Tensor_Printer<CharT, Traits, T, N>
{
    static void print(std::basic_ostream<CharT, Traits>& os, Tensor<T, N> t) {
        for (auto i = 0; i < N; ++i) {
            os << std::setw(4) << t[i] << ' ';
        }
        os << std::endl;
    };
};

template<typename CharT, typename Traits, typename T, std::size_t N, std::size_t... Ns>
struct Tensor_Printer<CharT, Traits, T, N, Ns...>
{
    static void print(std::basic_ostream<CharT, Traits>& os, Tensor<T, N, Ns...> t) {
        for (auto i = 0; i < N; ++i) {
            Tensor_View_Printer<CharT, Traits, T, product<N, Ns...>::value, Ns...>::print(os, t[i]);
            os << "---------" << std::endl;
        }
    };
};

template<typename CharT, typename Traits, typename T, std::size_t N, std::size_t... Ns>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, Tensor<T, N, Ns...> t) {
    Tensor_Printer<CharT, Traits, T, N, Ns...>::print(os, t);
    return os;
}

int main() {
    std::cout << "7D tensor:" << std::endl;
    
    Tensor<float, 2, 2, 2, 2, 2, 2, 2> t3;
    
    t3[0][0][0][0][0][0][0] = 1.1f;
    t3[0][1][1][0][0][1][0] = 2.2f;
    t3[1][1][1][1][0][0][0] = 3.3f;
    t3[1][1][0][1][1][0][0] = 4.4f;
    
    std::cout << t3;

    return 0;
}
