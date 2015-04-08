#include <string>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <list>
#include <chrono>
#include <utility>

struct foo {
    foo(){std::cout << "default constructed\n";}
    foo(const foo& rhs){std::cout << "copy constructed\n";}
    foo(foo&& rhs){std::cout << "move constructed\n";}
    foo& operator=(const foo& rhs){std::cout << "copy assigned\n"; return *this;}
    foo& operator=(foo&& rhs){std::cout << "move assigned\n"; return *this;}
    ~foo(){std::cout << "destroyed\n";}
};

template <typename T>
struct identity {
    constexpr auto operator()(T&& in) const noexcept -> decltype(std::forward<T>(in)){
        return std::forward<T>(in);
    }
};

template <typename Function>
struct identity_element;

//template <>
//struct identity_element<std::plus<int>>{
//    int operator()() const noexcept {
//        return 0;
//    }
//};

template <typename Integer, typename = typename std::enable_if<std::is_integral<Integer>::value, void>::type>
struct identity_element<std::plus<Integer>> {
    Integer operator()() const noexcept {
        return Integer{0};
    }
};

template <>
struct identity_element<std::plus<std::string>>{
    std::string operator()() const noexcept {
        return "";
    }
};


int main(){
//    std::chrono::steady_clock clk;
//    std::cout << clk.period;
//    std::cout << std::chrono::steady_clock::period().den << ' ' << std::chrono::steady_clock::period().num;
//    int arr[-1];
//    const int i = 1, *ip = &i;
    std::cout << identity<std::string>{}("Yello") << std::endl;
}