#include <functional>
using namespace std;
using namespace std::placeholders;

struct A {
    void func1(int a, double b) {
    }
};

static void func2(int a, double b) {
}

int main(int argc, const char *argv[]) {
    function<void(int, double)> f;
    f = func2;
    f(1, 2.);

    A a;
    auto f2 = bind(&A::func1, a, _1, _2);    
    f2(1, 2.);

    printf("This runs\n");
    return 0;
}