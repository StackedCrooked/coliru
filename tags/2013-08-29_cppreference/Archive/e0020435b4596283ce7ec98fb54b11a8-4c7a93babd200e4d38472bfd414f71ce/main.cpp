#include <stdio.h>
#include <functional>

template <typename T>
auto callback(T&& func) ->decltype(func())
{
    return func();
}

double test(double& value)
{
    value=value+1.0;
    return value;
}

int main(void)
{
    double t=1.0;
    printf("%f\n",t);
    test(t);
    printf("%f\n",t);
    callback(std::bind(test, std::ref(t)));
    printf("%f\n",t);
}
