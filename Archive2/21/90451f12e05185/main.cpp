#include <iostream>
#include <string>


class Test {
public:
    int get_field1() { return 42; }
    std::string get_field2() { return "str"; } 
};


#define FIELD(id) << #id "=" << ptr->get_##id()


int main()
{
    Test t;
    Test* ptr = &t;
    std::cout FIELD(field1) << std::endl;
    std::cout FIELD(field2);
}