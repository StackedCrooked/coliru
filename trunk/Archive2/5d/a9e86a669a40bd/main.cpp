

#define CAT(x, y) CAT_(x, y)
#define CAT_(x, y) x ## y
#define GET_SET(Name, Readonly) decltype(Name) CAT(get, Name)() const { return Name; } \
void CAT(set, Name)(decltype(Name) value = decltype(Name)()) { \
    static_assert(!Readonly, #Name " is read-only."); \
    Name = value; \
}

class Test
{
    int x;
    int y;
public:
    GET_SET(x, false)
    GET_SET(y, true)
};

#include <iostream>

int main()
{

    return 0;
}
