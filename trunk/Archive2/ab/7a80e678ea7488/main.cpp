#include <functional>
#include <iostream>
using namespace std;
using namespace std::placeholders;
int multiply(int a, int b)
{
    return a * b;
}
int main()
{
    auto f = bind(multiply, 5, _1);
    for (int i = 0; i < 10; i++)
    {
        cout << "5 * " << i << " = " << f(i) << endl;
     }
    return 0;
}