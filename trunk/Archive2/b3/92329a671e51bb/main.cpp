#include <initializer_list>

int main()
{
    for (auto c : { 1, 2, 3 }) { throw 42; };
}