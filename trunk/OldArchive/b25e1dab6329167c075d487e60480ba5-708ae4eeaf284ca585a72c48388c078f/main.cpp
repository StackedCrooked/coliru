#include <type_traits>
#include <iterator>

template <class InputIterator, class Function>
Function for_each_byval(InputIterator first, InputIterator last, Function f) {
    static_assert(!std::is_reference<Function>::value, "whoops: by ref?!");
    for(;first!=last;++first)
        f(*first);
    return std::move(f);
}

template <class InputIterator, class Function>
Function for_each_byref(InputIterator first, InputIterator last, Function&& f) {
    static_assert(std::is_reference<Function>::value, "whoops: not by ref?!");
    for(;first!=last;++first)
        f(*first);
    return std::forward<Function>(f);
}

int main()
{
    char buf[] = "hello world!";

    const auto f = [](char& ch){ch-=1;};
    for_each_byval(std::begin(buf), std::end(buf), f);
    for_each_byref(std::begin(buf), std::end(buf), f);

    puts(buf);
}
