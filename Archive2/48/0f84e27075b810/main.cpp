#include <utility>
#include <iostream>
#include <vector>

struct MyClass {
    template<class T> using MyTemplateType = std::vector<T>;
};

template<class MC>
class MyOtherClass {
    public:
        template<class T> using MyTType = typename MC::template MyTemplateType<T>;
    
        auto print() {
            MyTType<int> myVec = {42};
            std::cout << myVec[0] << "\n";
        }
};

int main()
{
    MyOtherClass<MyClass> x;
    x.print();
}