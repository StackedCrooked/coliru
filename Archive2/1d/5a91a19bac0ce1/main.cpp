#include <iostream>
#include <typeinfo>

using namespace std;

template<typename T>
void f(T t) {
    cout << typeid(t).name() << endl;
}

int main(int, char*[]) {
    f(1 == 0);
    f(0);
    f(0L);
    f(NULL);
    f(nullptr);
    return 0;
}