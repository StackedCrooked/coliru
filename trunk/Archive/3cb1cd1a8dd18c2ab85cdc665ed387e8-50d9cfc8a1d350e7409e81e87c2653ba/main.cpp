#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class MyClass
{
public:
    void run();
}

int main()
{
 std::vector<MyClass> v(10);
 
 std::for_each(v.begin(), v.end(), run);

    std::cout << "End \n";
}
