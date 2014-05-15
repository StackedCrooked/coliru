#include <cassert>
#include <iostream>
#include <vector>
#include <future>

using namespace std;

int foo() {
    int i = 0;
    while (i < 1000000)
        i++;
    return 10;
}

int main() {
    auto f(async(foo));
    int t = f.get(); // I think the program should block there

    cout<<t<<endl;
    return 0;
}