#include <iostream>

struct Test
{
    Test(){ std::cout << "Test()" << std::endl; }
    Test(Test&&){ std::cout << "Test(Test&&)" << std::endl; }
    Test(const Test&){ std::cout << "Test(const Test&)" << std::endl; }

    ~Test(){ std::cout << "~Test()" << std::endl; }
};

Test MakeTest()
{
    Test t;//output Test()

    return Test(t);//output Test(const Test&)
}//output ~Test

int main()
{
    std::cout << "------------------------------" << std::endl;
    Test t0(MakeTest()); //How is t0 constructed!??
    std::cout << "------------------------------" << std::endl;
    Test t1(std::forward<Test>(MakeTest())); //output Test(Test&&) \n ~Test
    std::cout << "------------------------------" << std::endl;

    return 0;
}//output ~Test \n ~Test