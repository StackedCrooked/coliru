template<class Derived>
class comparable {};

class A: public comparable<A>
{  };

class B: public comparable<B>
{ };

bool operator==(const A& a, const B& b) 
{ return true; }

template<class A, class B>
auto operator==(const A& a, const B& b) -> decltype(b==a) 
{ return b==a; }

template<class A, class B>
auto operator!=(const A& a, const B& b) -> decltype(!(a==b))
{ return !(a==b); }



int main() {
    A a;
    B b;
    a==b;
    b==a;
}