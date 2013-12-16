#include <iostream>
#include <vector>
class test
{
public:
    test()
    {
        std::cout<<"default construction of test"<<std::endl;
        std::cout<<"  -MEMORY ALLOCATION"<<std::endl;
    }
    test(const test& rhs) 
    {
        std::cout<<"copy construction of test"<<std::endl;
        std::cout<<"  -MEMORY ALLOCATION"<<std::endl;
    }
    ~test()
    {
        std::cout<<"destruction of test"<<std::endl;
        std::cout<<"  -MEMORY DEALLOCATION"<<std::endl;
    }
};
int main()
{
    std::vector<test> m(1);
    std::cout<<"main"<<std::endl;
    return 0;
}