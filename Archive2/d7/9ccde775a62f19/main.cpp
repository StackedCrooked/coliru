#include <iostream>

struct foo
{
    static void bar(foo &f)
    { std::cout << f.data_ << std::endl; }
    
private:
    int data_{ 42 };      
};

int main()
{
    foo f;
    foo::bar(f);
    std::cout << "good" << std::endl;
}