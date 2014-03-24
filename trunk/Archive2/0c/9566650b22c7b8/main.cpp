#include <functional>
#include <cstdio>

struct A {

    int value = 100;

    A() {
        printf("A\n");
    }

    A(const A& a) {
        printf("copy A\n");
    }
    
    A(A&&) {
        printf("move A\n");
    }

    ~A() {
        printf("~A\n");
    }
};

void function(std::function<int()> lambda) {
    printf("%d\n", lambda());
}

int main()
{
    A a;
    auto lambda = [a]() -> int {
        return a.value;
    };

    function(lambda);

    return 0;
}