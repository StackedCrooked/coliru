#include <sstream>
#include <iostream>

template<typename T_Type>
class TestTemplateClass {
private:
    T_Type _state;

public:
    TestTemplateClass() : _state() {
        std::cout << "Default constructor" << std::endl;
    }

    TestTemplateClass(int inState) : _state(inState) {
        std::cout << "State constructor" << std::endl;
    }

    template<typename T_OtherType>
    TestTemplateClass(const TestTemplateClass<T_OtherType> &inValue) {
        std::cout << "Template-copy constructor" << std::endl;
    }

    template<typename T_OtherType>
    void operator = (const TestTemplateClass<T_OtherType> &inValue) {
        std::cout << "Operator" << std::endl;
    }

    ~TestTemplateClass() {
        std::cout << "Destructor" << std::endl;
    }
};

TestTemplateClass<int> createFunction() {
    return TestTemplateClass<int>();
}

int main() {
    TestTemplateClass<int> theReference = createFunction();
    std::cout << "Finished" << std::endl;
    return 0;
}