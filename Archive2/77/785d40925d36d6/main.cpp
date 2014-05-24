#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct Tag{};

struct Test
{
    Test()
    {
        cout << "Constructor called" << endl;
    }
    ~Test()
    {
        cout << "Destructor called" << endl;
    }
};

shared_ptr<Test> fun(Tag)
{
    shared_ptr<Test> test = make_shared<Test>();   
    return test;
}

unique_ptr<Test> fun()
{
    unique_ptr<Test> test(new Test); 
    return std::move(test);
}

int main()
{
    shared_ptr<Test> test = fun(Tag{});
    shared_ptr<Test> test2 = test;
    std::cout << "Shared_ptr count : " << test2.use_count() << std::endl;
    
    unique_ptr<Test> test3 = fun();
    
}