#include <iostream>
 
template<class T>
class MyContainer{
public:
    MyContainer(const T& val):
    value_(val){}
     
     MyContainer(){};
    void test(){
        std::cout << value_;
    }
private:
    T value_;
};
 
int main(){
    MyContainer<int> container;
}