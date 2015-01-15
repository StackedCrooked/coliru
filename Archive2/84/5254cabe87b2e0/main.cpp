#include<iostream>
#include<string>

struct MyBigType {};

class MyClass {
public:
    void fmove(MyBigType&& a, int id){
        std::cout << "int\n";
    }
    void fmove(MyBigType&& a, std::string name){
        std::cout << "string\n";
    }
    void fmove(MyBigType&& a, int b, int c, int d){
        std::cout << "int, int, int\n";
    }

    template<class... Args>
    void f(const MyBigType& a, Args&&... args) {
        return fmove(MyBigType(a), std::forward<Args>(args)...);
    }
    template<class... Args>
    void f(MyBigType&& a, Args&&... args) {
        return fmove(a, std::forward<Args>(args)...);
    }
};

int main() {
    MyBigType const big;
    MyClass().f(big, 4);
    MyClass().f(big, "");
    MyClass().f(big, 4, 5, 6);
    MyClass().f(std::move(big), 4);
    MyClass().f(std::move(big), "");
    MyClass().f(std::move(big), 4, 5, 6);
}