#include <iostream>

class Integer { 
    int val;
public:
    Integer(int x) : val(x) {};
    
    Integer operator+(Integer const &x) { 
        return Integer(val + x.val);
    }
};

int main(){ 
    Integer a(1);
    
    Integer b = a + 1; // allowed
    Integer c = 1 + a; // Not allowed
}

