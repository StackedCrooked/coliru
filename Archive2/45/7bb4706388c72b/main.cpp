#include <iostream>
#include <memory>
#include <functional>

using namespace std;

int main()
{
    auto ptr = make_unique<int>(10);
    function<void()> f { [ptr=move(ptr)]{ cout << *ptr << endl; } };
}