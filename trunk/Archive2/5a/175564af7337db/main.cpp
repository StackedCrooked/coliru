#include <list>
#include <algorithm>

class MyClass
{
public:
 explicit MyClass(int) {};
 MyClass(MyClass&&) {}
 MyClass& operator=(MyClass&&) {return *this;}
private:
 MyClass(const MyClass&); // disabled, pre-C++11 syntax
 MyClass& operator=(const MyClass&); // disabled, pre-C++11 syntax
};

int main()
{
    std::list<MyClass> lst;
    std::remove_if(lst.begin(), lst.end(), [](MyClass& mcl) { return true; });
}