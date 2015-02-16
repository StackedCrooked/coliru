#include <iostream>

class Tester {
private:
    int m_value;
public:
    Tester(int value) : m_value(value){}

    int getValue(){
        return this->m_value;
    }

    bool compareOld(const Tester* b){
        int res = ((Tester*)b)->getValue();
        std::cout << "Old: " << this->m_value << " = " << res << std::endl;
        return (this->m_value == res);
    }
    
    bool compareNew(const Tester* b){
        int res = const_cast<Tester*>(b)->getValue();
        std::cout << "New: " << this->m_value << " = " << res << std::endl;
        return (this->m_value == res);
    }
};

int main()
{
    Tester* first = new Tester(4);
    Tester* second = new Tester(4);
    
    first->compareOld(second);
    first->compareNew(second);
    
    std::cout << "finished" << std::endl;
}