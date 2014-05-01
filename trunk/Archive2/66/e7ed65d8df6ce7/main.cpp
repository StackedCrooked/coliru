#include <iostream>

class MFWIDGETS{
    
};

class iWrap{
    int i;
public:
    iWrap(int i):i(i) {}   
    
    operator int() {return i;}
    operator MFWIDGETS* () { return new MFWIDGETS(); }
};

void i(int k) {std::cout<<k<<std::endl;}

int widme(MFWIDGETS* ) {
    // do nothing becus lazy
}

int main() {
    iWrap inuit(10);
    i(inuit);
    
    widme(inuit);
    
    return 0;
}