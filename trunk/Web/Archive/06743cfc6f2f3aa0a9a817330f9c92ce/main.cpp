#include <iostream>
#include <functional>
using std::cout;
using std::function;

int main(){
    [](int a) {
        std::function<void(int)> f = [&f] (int b){ 
            cout << b << '\n';
            if (b > 0)
                f(b-1);
        }; f(a);
    } (5);
}