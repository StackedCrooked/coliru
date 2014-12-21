#include <iostream>
#include <cstdlib>
#include <string> // *** required

template <class Type>
class Person // *** why is this a template?
{
private:
    int age = 0 ;
    std::string name = "anonymous" ;

public:
    std::ostream& print( std::ostream& stm = std::cout ) const
    { return stm << "{ " << name << ", " << age << " }" ; }

    const Person* operator->() const noexcept { return this ; } ; // *** why?
    Person* operator->() noexcept ; // *** why?

    static void* operator new(size_t);
    static void* operator new[] (size_t);
    static void operator delete(void*);
    static void operator delete[] (void*);

    Person(std::string ,int);
    Person() = default ;
};

template <class Type>
Person<Type>* Person<Type>::operator ->() noexcept
{
    return this;
}

template <class Type>
void* Person<Type>::operator new( size_t sz )
{
    std::cout << "Person<>::operator new: size == " << sz << '\n' ;
    return std::malloc(sz) ; // check for nullptr, throw on allocation failure?
}

template <class Type>
void* Person<Type>::operator new[] ( size_t sz )
{
    std::cout << "Person<>::operator new[]: size == " << sz << '\n' ;
    return std::malloc(sz) ; // check for nullptr, throw on allocation failure?
}

template <class Type>
void Person<Type>::operator delete(void* p)
{
    std::cout << "Person<>::operator delete: p == " << p << '\n' ;
    std::free(p) ;
}

template <class Type>
void Person<Type>::operator delete[] (void* p)
{
    std::cout << "Person<>::operator delete[] : p == " << p << '\n' ;
    std::free(p) ;
}



template <class Type>
Person<Type>::Person(std::string y, int x)
{
    name = y;
    age = x;
}

const int maxSize = 5;

int main()
{
//  The arrow operator
    Person<void> w("Ali Omar", 35);
    w.print() << ' ' ;
    w->print() << '\n' ;

    // **** The += operator has not been defined
    // w += 7;
    // w.print();
    // w->print();

    //  The new operator and delete operator // **** instead, use std::unique_ptr<>
    Person<int>* q = new Person<int> ("Omar Ali", 65); // use std::unique_ptr<>
    q->print() << '\n' ;
    delete q;

//  The new [ ] operator and delete operator // **** instead, use std::unique_ptr<>
    Person<double>* r = new Person<double>[maxSize];

    for(int i=0; i<maxSize; i++)
        r[i]->print() << '\n' ;

    delete [] r;
}
