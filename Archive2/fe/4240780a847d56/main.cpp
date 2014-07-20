#include <iostream>

template<typename t>
struct foo
{
    foo(t var)
    {
        std::cout << "Regular Template";
    }
};



template<typename t>
struct foo<t*>
{
    foo(t *var)
    {
        std::cout << "partially specialized Template " << var;
    }
};


int main()
{
    int* a = new int(12);

    foo<int*> f(a); //Since its a ptr type it should call specialized template

}
