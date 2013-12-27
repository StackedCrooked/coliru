#include <utility>
#include <iostream>

class Mutex
{
public:
    Mutex() {}
private:
    Mutex(const Mutex&);
    const Mutex& operator=(const Mutex&);
};

class Test
{
public:
    Test() {}

private:
//    Test(const Test&);
//    const Test& operator=(const Test&);

private:
    std::pair<bool, Mutex> p;
};
        
int main()
{
    std::pair<bool, Mutex> p;
    Test t;
    std::cout << "OK\n";
}
