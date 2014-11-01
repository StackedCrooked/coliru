#include <iostream>
#include <vector>
#include <string>
using namespace std;


template <typename ... T>
void Print(T ... ty)
{
    auto size = sizeof...(T);
    cout << "size of : " << size << endl;

    T vs[] = {ty...};
}

int main()
{
    Print(1, 3, 5, 6);

    return 0;
}

