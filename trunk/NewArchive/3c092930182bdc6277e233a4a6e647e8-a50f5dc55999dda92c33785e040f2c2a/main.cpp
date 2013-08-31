const char * a_cpp = R"cc(

    #include <iostream>
    
    struct Test
    {
        Test()
        {
            std::cout << "Hello from a.cpp!" << std::endl;
        }
    };
    
    Test a;
    
)cc";

const char * b_cpp = R"cc(

    #include <iostream>
    
    struct Test
    {
        Test()
        {
            std::cout << "Hello from b.cpp!" << std::endl;
        }
    };
    
    Test b;    
    
)cc";


const char * test_cpp = R"cc(

    int main() {}
    
)cc";


#include <fstream>
#include <iostream>

int main()
{
    std::cout << "write a.cpp" << std::endl;
    std::ofstream a("a.cpp");
    a << a_cpp;
    
    std::cout << "write b.cpp" << std::endl;
    std::ofstream b("b.cpp");
    b << b_cpp;
    
    std::cout << "write test.cpp" << std::endl;
    std::ofstream test("test.cpp");
    test << test_cpp;
}