#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class A
{
public:
    A()
    {
        cout << "created" << endl;
    }

    ~A()
    {
        cout << "destroyed" << endl;
    }
};

struct B {
    B() { std::cout << "Enter main scope" << std::endl; }
    ~B(){ std::cout << "End main scope" << std::endl; } } printer; 

int main()
{
    std::cout << "Enter some scope" << std::endl;
    {//some scope
        std::vector<std::shared_ptr<A>> vec;
        vec.push_back(std::make_shared<A>());

        vec.pop_back();
    }
    std::cout << "End some scope" << std::endl;

    //2. если поставить бряк здесь, что будет в консоле?
}
