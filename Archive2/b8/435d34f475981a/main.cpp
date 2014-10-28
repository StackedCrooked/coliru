#include <boost/lambda/lambda.hpp>
#include <iostream>

int main()
{
    auto lambda = boost::lambda::constant(3);
    std::cout << lambda() << std::endl;
}
