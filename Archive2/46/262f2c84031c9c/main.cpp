#include <iostream>
#include <typeinfo>

using namespace std;

int sum(int a, int b){
    return a + b;
}

int main()
{
    float sum(int, int); // redeclaring sum???
    int a = -1;
    auto result = sum(a, a);
    cout << result << typeid(result).name() << endl;
}
