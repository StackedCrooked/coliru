#include <memory>

struct SomeType { };
struct TypeDerivedFromSomeType : SomeType { };

struct BaseClass
{
   template<typename PtrType = BaseClass> using Ptr = std::shared_ptr<PtrType>;
   // ...
};

struct DerivedClass : public BaseClass
{
    //...
    BaseClass::Ptr<SomeType> GetChild() { return m_child; }

    BaseClass::Ptr<SomeType> m_child;
    //..
};

template<typename T>
struct EvenMoreDerivedClass : public DerivedClass
{
    // ...
    void MethodUsingChildClass();
    // ... 
};

template<typename T>
void EvenMoreDerivedClass<T>::MethodUsingChildClass()
{
    BaseClass::Ptr<TypeDerivedFromSomeType> child = GetChild(); // Surely this should fail?
    // more code
}

int main() {
    EvenMoreDerivedClass<int> c;
    c.MethodUsingChildClass();
}