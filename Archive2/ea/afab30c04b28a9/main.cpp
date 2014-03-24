#include <iostream>
#include <memory>

struct A
{
    A(int a){}
};

int main(int argc, char** argv) {
    std::unique_ptr<A[]> a(new A[2]{A(1), A(2)});
    return 0;
}