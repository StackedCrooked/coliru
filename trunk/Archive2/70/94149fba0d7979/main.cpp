#include <type_traits>

template <typename T>
using alias = T;

template <bool B>
struct Bool : std::integral_constant<bool, B> {};

typedef Bool<true> True;
typedef Bool<false> False;

template <typename T>
struct enable_if_t : std::enable_if<T::value, int> {};
template <typename T>
struct disable_if_t : std::enable_if<!T::value, int> {};

template <typename T>
using Invoke = typename T::type;

template <typename T>
using EnableIf = Invoke<enable_if_t<T>>;

template <typename T>
using DisableIf = Invoke<disable_if_t<T>>;


#include <array>
#include <algorithm>
using std::array;

template <typename T, typename S, size_t N, typename BinaryOp,
          EnableIf<std::is_same<typename std::result_of<BinaryOp(const T&, const S&)>::type, T>> = 0>
array<T, N>& combine(array<T, N>& left, const array<S, N>& right, BinaryOp&& func)
{
    std::transform(left.begin(), left.end(), right.begin(), left.begin(), func);
    return left;
}

template <typename T, typename S, size_t N, typename BinaryOp,
          EnableIf<std::is_same<typename std::result_of<BinaryOp(T&, const S&)>::type, void>> = 0>
array<T, N>& combine(array<T, N>& left, const array<S, N>& right, BinaryOp&& func)
{
    for (size_t i = 0; i < N; i++)
    {
        func(left[i], right[i]);
    }
    return left;
}

#include <iostream>

template <typename T, typename S, typename BinaryOp>
void test(BinaryOp&& func)
{
    bool b = std::is_same<typename std::result_of<BinaryOp(T&, const S&)>::type, T>::value;
    std::cout << b << "\n";
    b = std::is_same<typename std::result_of<BinaryOp(T&, const S&)>::type, void>::value;
    std::cout << b << "\n";
}

int main()
{
    std::cout << "int(const int&, const int):\n";
    test<int, int>([](const int& left, const int& right){ return left + 3 * right; });
    std::cout << "void(int&, const int):\n";
    test<int, int>([](int& left, const int& right){ left += 3 * right; });
}