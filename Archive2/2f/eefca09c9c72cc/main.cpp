#include <iostream>
struct S
{
    mutable int mi;
    int f(int n) { return mi+n; }
    S(int n) : mi(n) {}
};
struct D : public S {
        D(int n) : S(n) {}
};
 
int main()
{
    int S::* pmi = &S::mi;
    int (S::*mpf)(int) = &S::f;
 
    const S s(7);
//    s.*pmi = 10; // cannot modify through mutable
    std::cout << s.*pmi << '\n';
 
    D d(7); // base pointers work with derived object
    D* dp = &d;
    std::cout << (d.*mpf)(7) << ' '
              << (dp->*mpf)(8) << '\n';
}