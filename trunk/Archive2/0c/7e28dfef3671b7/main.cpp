#include <iostream>

auto lambda = [](){ std::cout << "hello\n"; };
typedef decltype(lambda) lambda_t;
void func(lambda_t l) { l(); }

int main()
{
    lambda_t l2 = lambda;
    func(l2);
}
