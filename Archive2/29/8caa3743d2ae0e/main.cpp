#include <string>
#include <iostream>
 
struct A {
    std::string s;
    A() : s("test") { std::cout << "construct a !" << std::endl;}
    A(const A& o) : s(o.s) { std::cout << "move failed!\n";}
    A(A&& o) : s(std::move(o.s)) {std::cout << "move successful!\n";}
    ~A(){std::cout << "deconstrcut ~A!" << std::endl;}
};

#if 0
A f(A a) {
    return a;
}
#endif

#if 1
A f(A&& a) {
    return a;
}
#endif

#if 0
A&& f(A&& a) {
    return std::move(a);
}
#endif

int main()
{
    A a_obj;
    //A b_obj = f(a_obj);
    A b_obj = f(std::move(a_obj));
    
    return 0;

}