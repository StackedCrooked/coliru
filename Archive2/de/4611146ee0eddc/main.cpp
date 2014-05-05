#include <iostream>
#include <thread>
#include <memory>
#include <vector>
using namespace std;
class test
{
    public:
    test() { cout<<"test::test"<<endl;}
    ~test() { cout<<"~test::test"<<endl;}
};
int main()
{
    shared_ptr<test> pt(new test());
}