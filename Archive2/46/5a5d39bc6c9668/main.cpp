#include <memory>
#include <string>
#include <iostream>
using namespace std;

class MyClass{
    class innerC{
        int value;
    };
    innerC inner;
    public:
    innerC& getInnerC(){
        return &inner;
    }
};

int main(){    
    MyClass obj;
    innerC c = obj.getInnerC();
    return 0;
}