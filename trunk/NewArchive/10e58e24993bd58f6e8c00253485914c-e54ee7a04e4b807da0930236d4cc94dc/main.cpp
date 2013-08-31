#include <cstdlib>
#include <iostream>

class Test{
    public:
    virtual void test(){
        std::cout<<"test"<<std::endl;
    }
};

int main(){
    Test t;
    t.test();
}
