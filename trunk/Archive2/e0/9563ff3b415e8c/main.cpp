#include <cstdlib>
#include <cstdio>

struct abc {
    void *test;
};

struct def {
    int a;
    int b;
};

int main()
{
    abc *mystruct = static_cast<abc*>(malloc(sizeof(abc)));
    mystruct->test = malloc(sizeof(def));
    static_cast<def*>(mystruct->test)->a = 3;
    printf("%d\n", static_cast<def*>(mystruct->test)->a);
    
    return 0;
}