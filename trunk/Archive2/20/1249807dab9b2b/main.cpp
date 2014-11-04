#include <string>
#include <iostream>

struct S {
    std::string a;
    int b;
    
//    S(const S&) = default;
//    S(S&&) = default;
//    S& operator=(const S&) = default;
//    S& operator=(S&&) = default; // not required here but should be added for completeness
    
    ~S() {
        std::cout << a << " " << b << std::endl;
    }
};

S f(S arg) {
    S s0{};
    S s1(s0); //s1 {s0}; in the book
    s1 = arg;
    return s1;
}

int main()
{
    S s3{"tool",42};
    f(s3);
    //S s2 = std::move(s3);
}