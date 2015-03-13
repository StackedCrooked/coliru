#include <iostream>

template <typename TSubclass>
class Parent {
public:
    void callSubclassFunction() {
        static_cast<TSubclass*>(this)->functionToBeCalledFromParent();
    }
};

template <typename TSubclass>
class Child : public Parent<TSubclass> {
};

class SubChild : public Child<SubChild> {
public:
    void functionToBeCalledFromParent() {
        std::cout << "SubChild!" << std::endl;
    }
};

int main()
{
    SubChild child;
    child.callSubclassFunction();
}
