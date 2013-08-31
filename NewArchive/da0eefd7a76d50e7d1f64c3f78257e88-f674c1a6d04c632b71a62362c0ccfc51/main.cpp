#include <iostream>

#include <boost/tuple/tuple.hpp>
#include <boost/function.hpp>

typedef boost::function<void(int)>      func_1int_t;
typedef boost::function<void(int, int)> func_2int_t;
typedef boost::function<void(char)>     func_1char_t;

typedef boost::tuple<func_1int_t, func_2int_t, func_1char_t> func_container_t;

void f1(int a_1)
{
    std::cout << "f1: " << a_1 << std::endl;
}
void f2(int a_1, int a_2)
{
    std::cout << "f2: " << a_1 << ", " << a_2 << std::endl;
}

void f3(char a_1)
{
    std::cout << "f1: " << a_1 << std::endl;
}

int main()
{
    func_container_t funcs = boost::tie(f1, f2, f3);

    funcs.get<0>()(1);
    funcs.get<1>()(2, 3);
    funcs.get<2>()('4');
}
