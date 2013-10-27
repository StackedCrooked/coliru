#include <iostream>
#include <string>
#include <vector>

class X
{
private:
    static inline int silly_fun(int a) {
        // imagine some complex computation based on a
        return 0;
    }
public:
    const int a;
    X(int a):a(silly_fun(a)) {}
};
class Y
{
public:    
    const int a;
    Y(int a):a(([](int a) {
        // imagine the same complex computation based on a
        return 0;
    })(a)) {}
};

int main()
{
    X a(1);
    Y b(1);
    return 0;
}
