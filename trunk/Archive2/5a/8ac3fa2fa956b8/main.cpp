#include <iostream>
#include <cstdlib>
#include <string> // *** required
#include <algorithm> // for std::min

class Person 
{
private:
    int age = 0 ;
    std::string name = "anonymous" ;

public:
    std::ostream& print( std::ostream& stm = std::cout ) const
    { return stm << "{ " << name << ", " << age << " }\n" ; } // '\n' because 'no change to main()

    const Person* operator->() const { return this ; } ; // *** why ?
    Person* operator->(); // *** why ?

    static void* operator new(size_t);
    static void* operator new[] (size_t);
    static void operator delete(void*);
    static void operator delete[] (void*);

    // the += operator
    Person& operator+= ( int y ) { age = std::min( 0, age+y ) ; return *this ; }
    Person& operator-= ( int y ) { return *this += -y ; }

    // the + operator
    friend inline Person operator+ ( Person p, int y ) { return p += y ; }
    friend inline Person operator- ( Person p, int y ) { return p += -y ; }

    Person(std::string ,int);
    Person() = default ;
};

Person* Person::operator ->()
{
    return this;
}

void* Person::operator new( size_t sz )
{
    std::cout << "Person<>::operator new: size == " << sz << '\n' ;
    return std::malloc(sz) ; // check for nullptr, throw on allocation failure?
}

void* Person::operator new[] ( size_t sz )
{
    std::cout << "Person<>::operator new[]: size == " << sz << '\n' ;
    return std::malloc(sz) ; // check for nullptr, throw on allocation failure?
}

void Person::operator delete(void* p)
{
    std::cout << "Person<>::operator delete: p == " << p << '\n' ;
    std::free(p) ;
}

void Person::operator delete[] (void* p)
{
    std::cout << "Person<>::operator delete[] : p == " << p << '\n' ;
    std::free(p) ;
}

Person::Person(std::string y, int x)
{
    name = y;
    age = x;
}

const int maxSize = 5;

int main()
{
//  The arrow operator
    Person w("Ali Omar", 35);
    w.print();
    w->print();

//  The += operator
    w += 7;
    w.print();
    w->print();

//  The new operator and delete operator
    Person *q;
    q = new Person("Omar Ali", 65);
    q->print();
    delete q;

//  The new [ ] operator and delete operator
    Person *r;
    r = new Person[maxSize];

    for(int i=0; i<maxSize; i++)
        r[i]->print();

    delete [ ] r;

    return 0;
}
