#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <atomic>
template<typename T>
class MyClass
{
public:
    void set(T value)
    {
        mValue = value;
    }
    
    T get() const
    {
        return mValue;
    }
    
private:
    T mValue;    
};


int main()
{
    std::atomic<MyClass<int>*> inst;
    inst = new MyClass<int>;
    
    
}
