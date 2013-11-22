#include<iostream>

class Ciao{
    const Ciao(){};
};


int main(){
    int A = 3;
    {
        const int& A2 = A;
        int* b = const_cast<int*> (&A2);
        int& a = const_cast<int &>(A2);
        a = 5;
        *b= 5;
        std::cout<< A << '\t' << a << '\t' << &A <<'\t' << b << std::endl;
    }
    
    return 0;
}
