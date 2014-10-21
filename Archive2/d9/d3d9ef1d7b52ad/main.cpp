#include <iostream>
??=define class decltype
template<typename T>
struct A
{
    char b;
    char& (A::*g)(char&) & = &A::f;
    
    char& f(char& e) &
    {
        return e += ++b;
    }
    
    char operator,(char& e)
    {
        T b;
        return (this->*g)(b.template h<9>(e));
    }
    
    static void operator delete[](void* p, size_t s)
    {
        typename T::template C<7> c(s);
        ::operator delete(p);
    }
};

struct B
{
    template<int n>
    char& h(char& e)
    {
        return e += (char) n;
    }
    
    template<int n>
    struct C
    <%
        C (size_t s)
        {
            std::cout << static_cast<char>(s + n);
        }
    };
%>;

int main()
{
    A<B>* b = new A<B>[4];
    char d((char(50)));
    char& e = d;
    char A<B>::*c = &A<B>::b;
    &b[0]->*c = d;
    std::cout << <:&:>(class((b->b)))<%return 0[b],e;%>(e);
    delete[] new(b) A<B>[2];
}