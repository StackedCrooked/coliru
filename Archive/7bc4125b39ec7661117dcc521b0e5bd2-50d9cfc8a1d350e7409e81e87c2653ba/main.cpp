#include <iostream>
#include <string>
#include <vector>

class Animal { };
class Sheep : Animal { };
class Chicken : Animal { };

template<class T> class House { std::vector<T> l;  };
class Cage : House<Sheep> { };
class Hen : House<Chicken> { };

template<class T> class var1 { public: T data; T get(){return data;} void set(T t){data=t;} };
template<class A, class B> class var2 { public: var1<A> a; var1<B> b; };
template<class A, class B, class C> class var3 { public: var1<A> a; var1<B> b; var1<C> c; };

template<class T> class var { public: T data; T get(){return data;} void set(T t){data=t;} };
class any { };
class Int : any { public: int value; };
class Short : any { public: short value; };
class Long : any { public: long value; };
// ...
template<class T> class GenericList { std::vector<T> list; void add (T val){ list.insert(val); } };
class VarList : GenericList<var<any>> { };

int main()
{
    std::cout << "test" << std::endl;
}
