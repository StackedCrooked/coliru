#include <utility>

int main()
{
    int i = 42;
    double j = reinterpret_cast<double&&>(std::move(i));
}