#include <iostream>
#include <tuple>


template<unsigned N>
struct printer : printer<N - 1>
{
    template<typename ...Args>
    printer(const std::tuple<Args...> & tup) : printer<N - 1 >(tup)
    {
        std::cout << std::get<N-1>(tup) << " ";
    }
};


template<>
struct printer<0>
{
    template<typename T>
    printer(const T &) {}
};


template<typename ...Args>
void print(const std::tuple<Args...> & tup)
{
    printer<sizeof...(Args)>{tup};
}


int main()
{
    print(std::make_tuple(1, 2, 3));
}

