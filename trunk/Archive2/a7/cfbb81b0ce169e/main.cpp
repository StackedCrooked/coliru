#include <ostream>
#include <iostream>
#include <string>
#include <vector>

#define stringify(name) # name

enum Test 
{
    VALUE_1,
    VALUE_2,
    VALUE_3
};

Test getvalue() { return VALUE_1; }

int main()
{
    std::cout << stringify(VALUE_1) << std::endl;
    std::cout << stringify(getValue()) << std::endl;
}
