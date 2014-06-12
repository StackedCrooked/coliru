template<class Derived>
class comparable {};

class A: public comparable<A>
{  };

class B: public comparable<B>
{ };

bool operator==(const A& a, const B& b) 
{ return true; }

// this define all reverses
template<class T, class U>
bool operator==(const comparable<T>& sa, const comparable<U>& sb)
{ return static_cast<const U&>(sb) == static_cast<const T&>(sa); }

//this defines inequality
template<class T, class U>
bool operator!=(const comparable<T>& sa, const comparable<U>& sb)
{ return !(static_cast<const T&>(sa) == static_cast<const U&>(sb)); }



int main() {
    A a;
    B b;
    a==b;
    b==a;
}