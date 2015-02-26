#include <vector>
#include <iostream>
#include <iomanip>

struct MyClass {
    MyClass() { }
    MyClass(const MyClass&) { std::cout << "Copy construct" << std::endl; }
    MyClass(MyClass&&) noexcept { std::cout << "Move construct" << std::endl; }
    ~MyClass() { }
};

class Test
{
public:
//    Test() { _MyClass.reserve(10); }

    void pass_by_lvalue_ref(const MyClass& myClass)
    {
        _MyClass.push_back(myClass);
    }

    void pass_by_rvalue_ref(MyClass&& myClass)
    {
        _MyClass.push_back(std::move(myClass));
    }

    void pass_by_value(MyClass myClass)
    {
        _MyClass.push_back(std::move(myClass));
    }
private:
    std::vector<MyClass> _MyClass;
};

int main()
{
    MyClass myClass;
    Test Test;
    std::cout << "--lvalue_ref--\n";
    Test.pass_by_lvalue_ref(myClass);
    std::cout << "--rvalue_ref--\n";
    Test.pass_by_rvalue_ref(MyClass{});
    std::cout << "--value - lvalue--\n";
    Test.pass_by_value(myClass);
    std::cout << "--value - rvalue--\n";
    Test.pass_by_value(MyClass{});
}
