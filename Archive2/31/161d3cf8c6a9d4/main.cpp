#include <utility>
#include <iostream>
#include <vector>

template<class T> using MyTemplateType = std::vector<T>;

template<class MC>
class MyOtherClass {
    public:
        template<class T> using MyTType = MyTemplateType<T>;
        
        auto print() {
            MyTType<int> myVec = {42};
            std::cout << myVec[0] << "\n";
        }
};

int main()
{
    MyOtherClass<int> x;
    x.print();
}