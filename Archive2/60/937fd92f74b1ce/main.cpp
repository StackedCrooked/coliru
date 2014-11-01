#include <string>
#include <iostream>
#include <vector>
#include <memory>

struct A {
    std::string s;
    A() : s("test") {}
    //private:
    //A(const A& o) : s(o.s) { std::cout << "move failed!\n";}
    //public:
    //A(A&& o) : s(std::move(o.s)),p(std::move(o.p)) { std::cout << "move okay!\n"; }
    //private:
    std::unique_ptr<int> p;
};

template<class T>
T f(T a) {
    return a;
}
 
struct B : A {
     std::string s2; 
     int n;
     // implicit move contructor B::(B&&)
     // calls A's move constructor
     // calls s2's move constructor
     // and makes a bitwise copy of n
};
 
struct C : B {
    ~C() {}; // destructor prevents implicit move ctor C::(C&&)
};
 
struct D : B {
    D() {}
    ~D() {}; // destructor would prevent implicit move ctor D::(D&&)
    D(D&&) = default; // force a move ctor anyway
};

int main()
{
    std::cout << "---Trying to move A\n";
    A a1 = f(A()); // move-construct from rvalue temporary
    A a2 = std::move(a1); // move-construct from xvalue
    {
    std::vector<A> v;
    v.push_back(A());
    v.emplace_back();
    }
    std::cout << "---Trying to move B\n";
    B b1;
    std::cout << "Before move, b1.s = \"" << b1.s << "\"\n";
    B b2 = std::move(b1); // calls implicit move ctor
    std::cout << "After move, b1.s = \"" << b1.s << "\"\n";
 
    {
    std::vector<B> v;
    v.push_back(B());
    v.emplace_back();
    }
 
    std::cout << "---Trying to move C\n";
    C c1;
    //C c2 = std::move(c1); // calls the copy constructor
    
    {
    std::vector<C> v;
    //v.push_back(C());
    //v.emplace_back();
    }
    
    std::cout << "---Trying to move D\n";
    D d1;
    D d2 = std::move(d1);
    
    {
    std::vector<D> v;
    v.push_back(D());
    v.emplace_back();
    }
}