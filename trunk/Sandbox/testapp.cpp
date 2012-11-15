#include <fstream>
#include <iostream>


void test_open_readonly()
{
    std::ifstream read("main.cpp");
    std::string s;
    while (read >> s) {
        std::cout << s;
    }
}


void test_open_create()
{
    std::ofstream create("open_create");
    create << "Created!" << std::endl;
}


int main()
{
    test_open_readonly();
    test_open_create();
}
