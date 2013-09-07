#include <iostream>
using namespace std;

decltype(nullptr) g()
{
    cout << "foo" << endl;
    return nullptr;
}

int* f()
{
    return g();
}

int main(int argc, char** argv)
{
    auto x = f();
}