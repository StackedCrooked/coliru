#include<iostream>

template<class T>
void getLambda(T lambda){
    std::cout<< lambda(5);
}


auto foo() {
    int *a=new int;
    *a=4;
    std::cout<<*a<<"\n";
    auto lambda=[&a](int val){return (*a)+val;};
    return lambda;
}

int main ()
{
    getLambda(foo());
}
