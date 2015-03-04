#include <cmath>
#include <cstdio>

struct intishthing{
    int thing;
};

intishthing foo(const float& floaty){
    int inty = static_cast<int>(std::floor(floaty));
    //return intishthing{inty};
}

int main()
{
    float f = 55.9;
    printf("%f %i", f, foo(f).thing);    
}