#include <iostream>

struct wrapped_int{
    int value;
};

const int & operator+=(int& i, const wrapped_int& k){
    return i += k.value;   
}

int main()
{
    int a = 21;
    const wrapped_int z = {21};
    a += z;
    
    std::cout << a << std::endl;
    return 0;
}