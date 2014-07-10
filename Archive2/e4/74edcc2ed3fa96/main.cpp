#include <mutex>
int f()
{
    return 2;
}
int main()
{

const int& x2 = f();
}