#include <iostream>
#include <vector> 

using T = int;

class A{
 private:
        std::vector<T> &x;
 public:
        A(std::vector<T>& x_):x(x_) {}
        int func();
 };
 
 int A::func() {
     // process done
     T temp;
     x.push_back(temp);
     return 0;
}

int main() {
    std::vector<T> vec;
    A a(vec);
    a.func();
    std::cout << vec.size();
}