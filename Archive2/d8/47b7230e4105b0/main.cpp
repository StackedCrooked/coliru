#include <iostream>
#include <string>
#include <vector>
namespace aaa{
    class A{
        public:
    void f(int b){
        std::cout<<__FILE__<<" "<<__FUNCTION__<<std::endl;
        }
    };
}
int main()
{
    aaa::A a;
    a.f(0);
}