#include <functional>
#include <iostream>

class Button{
    int m_a;

public:
    Button(std::function<void(int&)> func1, std::function<void(int&)> func2):
    m_a(0)
    {
        func1(m_a);
        func1(m_a);
        func1(m_a);
        func2(m_a);
        std::cout << "After 3 increments and one decrement, m_a= " << m_a << std::endl;
    }
};

int main(){    
    Button myButton([](int &a){a++;}, [](int &a){a--;});

    return 0;
}