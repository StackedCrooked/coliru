#include <iostream>

template<typename T> class AbsClass{
public:
    virtual void func(const T* elem) = 0;
};

class SolidClass : public AbsClass<char>{
public:
    void func(const char* elem) { std::cout << elem << std::endl; }
};

int main(){
    SolidClass so;
    so.func("xyz");
}