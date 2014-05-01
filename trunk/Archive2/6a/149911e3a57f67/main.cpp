#include <iostream>

class iWrap{
    int i;
public:
    iWrap(int i):i(i) {}   
    
    operator int() {return i;}
};

void i(int k) {std::cout<<k<<std::endl;}
int main() {
    iWrap inuit(10);
    i(inuit);
    
    return 0;
}