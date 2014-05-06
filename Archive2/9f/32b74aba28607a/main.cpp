#include <type_traits>

//ForwarDeclared wenn der template typ nicht fix vorgegeben/ bzw. veränderbar sein soll
//ForwarDeclared1 wenn der template typ fix vorgegeben sein soll
//ForwarDeclared2 quasi normal forward declared


template<typename T>
class TempTest;
template<typename T>
using ForwardDeclared=TempTest<T>;

class ClassTest;
using ForwardDeclared1=TempTest<ClassTest>;
//class ForwardDeclared1; //funktioniert nicht, siehe dazu auch zb http://stackoverflow.com/questions/16966686/forward-declare-typedef-within-c-class da steht dass forward declare von typedefs nicht geht und auch etwas genauer warum

class ForwardDeclared2;

void TestFunction(ForwardDeclared<int> *p1);
void TestFunction1(ForwardDeclared1 *p1);
void TestFunction2(ForwardDeclared2 *p2);

int main()
{    
    ForwardDeclared<int> * p = nullptr;
    TestFunction(p);
    
    ForwardDeclared1 * p1 = nullptr;
    TestFunction1(p1);
    
    ForwardDeclared2 * p2 = nullptr;
    TestFunction2(p2);
}

//Ab hier kann man sich vorstellen dass ein anderes cpp file anfängt:

template<typename T>
class TempTest
{
public:
    T* m_pt;        
};

class ClassTest
{
public:
    int* m_pi;        
};

void TestFunction(ForwardDeclared<int> *p)
{
    p=p;
}

void TestFunction1(ForwardDeclared1 *p1)
{
    p1->m_pt=p1->m_pt;
    p1->m_pt->m_pi=p1->m_pt->m_pi;
    static_assert(std::is_same<decltype(p1->m_pt), ClassTest*>::value, "not same");
    static_assert(std::is_same<decltype(p1->m_pt->m_pi), int*>::value, "not same");
}

void TestFunction2(ForwardDeclared2 *p2)
{
    p2=p2;
}