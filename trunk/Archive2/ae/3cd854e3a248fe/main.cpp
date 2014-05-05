#include <initializer_list>
#include <iostream>

using namespace std;

template<typename ...Ts>
void print(Ts... xs)
{
    (void)initializer_list<int>{ (cout << xs << " ", 0)... };
}

int main()
{
    print(1, '2', "34");
}
