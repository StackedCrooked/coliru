#include <iostream>
using namespace std;
void prefix() { cout << "prefix "; }
void suffix() { cout << "suffix "; }

class Person{
    std::string mName;
public:
	Person(std::string pName) : mName(pName){}
	void printName(){
        std::cout << mName << " ";
	}
};

template <class T >
class Call_proxy;

template <class T >
class Wrap {
	T* p ;
public:
	Wrap (T* pp) : p(pp) {}
    Call_proxy<T> operator->() {
        cout << "Wrap-> ";
        prefix();
        return Call_proxy<T>(p);
    }
};

template <class T >
struct Call_proxy {
	T* p ;
	Call_proxy(T* pp) : p(pp) { cout << "Call_proxy{} "; }
	~Call_proxy() { suffix (); }
	T* operator->() { cout << "Call_proxy-> "; return p; }
};
 
 
int main()
{
	Wrap<Person> person(new Person("test"));
	person->printName();
}