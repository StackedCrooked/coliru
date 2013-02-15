#include <iostream>
#include <thread>
#include <functional>

using namespace std;
using namespace std::placeholders;

class SomeType  {
    int number;
 
public:
    SomeType(int new_number) : number(new_number) {}
    SomeType() : SomeType(42) {}
    int getNumber() { return number; }
    void setNumber(int num) { number = num; }
};

int main()
{
    
    cout << "Hello GCC " << __VERSION__ << "!" << endl;
    thread t([](){ cout << "Hello Thread!" << endl; });
    t.join();
    
    SomeType x;
    cout << "number is " << x.getNumber() << endl;
    
    auto some_strange_callable_type = bind(&SomeType::setNumber, &x, _1);
    
    some_strange_callable_type(20);
    
    cout << "number is now " << x.getNumber() << endl;
}
